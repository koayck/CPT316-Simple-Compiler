/**
 * @file Parser.cpp
 * @brief Implementation of the recursive descent parser for MiniLang
 *
 * This file implements a recursive descent parser that converts tokens into an Abstract Syntax Tree (AST).
 * It follows the grammar rules of MiniLang and handles:
 * - Statements (if, while, print, input, assignments, declarations)
 * - Expressions (arithmetic, comparison, variables, literals)
 * - Error reporting with line numbers
 */

#include "Parser.h"
#include "AST.h"
#include <iostream>
#include <memory>

using namespace std;

/**
 * @brief Main parsing function that processes all tokens into statements
 *
 * @param tokens Vector of tokens from lexical analysis
 * @return vector<StmtPtr> Vector of parsed statements
 */
vector<StmtPtr> parse(const vector<Token> &tokens)
{
  ParserState state(tokens);
  vector<StmtPtr> statements;

  while (!isAtEnd(state))
  {
    statements.push_back(parseStatement(state));
  }
  return statements;
}

/**
 * @brief Helper functions for token manipulation
 */
bool isAtEnd(const ParserState &state)
{
  return peek(state).type == TokenType::EOF_TOKEN;
}

Token peek(const ParserState &state)
{
  return state.tokens[state.current];
}

Token peekNext(const ParserState &state, int lookahead)
{
  return state.tokens[state.current + lookahead];
}

Token previous(const ParserState &state)
{
  return state.tokens[state.current - 1];
}

Token advance(ParserState &state)
{
  if (!isAtEnd(state))
  {
    state.current++;
  }
  return previous(state);
}

bool check(const ParserState &state, TokenType type)
{
  return !isAtEnd(state) && peek(state).type == type;
}

bool match(ParserState &state, TokenType type)
{
  if (check(state, type))
  {
    advance(state);
    return true;
  }
  return false;
}

/**
 * @brief Parses a single statement based on the current token
 *
 * Handles:
 * - If statements
 * - While loops
 * - Print statements
 * - Type declarations
 * - Assignments
 * - Input statements
 *
 * @param state Current parser state
 * @return StmtPtr Pointer to the parsed statement
 * @throws runtime_error if parsing fails
 */
StmtPtr parseStatement(ParserState &state)
{
  cout << "debug" << endl;
  try
  {
    if (match(state, TokenType::IF))
    {
      return parseIf(state);
    }
    if (match(state, TokenType::WHILE))
    {
      return parseWhile(state);
    }
    if (match(state, TokenType::PRINT))
    {
      return parsePrint(state);
    }
    if (match(state, TokenType::TYPE_INT) ||
        match(state, TokenType::TYPE_DOUBLE) ||
        match(state, TokenType::TYPE_STRING) ||
        match(state, TokenType::TYPE_BOOL))
    {
      return parseTypeDeclaration(state);
    }
    if (peek(state).type == TokenType::IDENTIFIER &&
        peekNext(state).type == TokenType::ASSIGN)
    {
      cout << "ASSIGN" << endl;
      if (peekNext(state, 2).type == TokenType::READ ||
          peekNext(state, 2).lexeme == "r")
      {
        cout << "INPUT" << endl;
        cout << peekNext(state, 2).lexeme << endl;
        return parseInput(state);
      }
      return parseAssignment(state);
    }

    throw runtime_error("Expected statement");
  }
  catch (const runtime_error &e)
  {
    if (string(e.what()).find("Line") == string::npos)
    {
      throw runtime_error("Line " + to_string(peek(state).line) + ": " + e.what());
    }
    throw;
  }
}

/**
 * @brief Parses an input statement in the form: variable = r("prompt");
 * 
 * This function handles both standalone input statements and input statements
 * within type declarations. The syntax is:
 * - Simple input: x = r("Enter x: ");
 * - Typed input: int x = r("Enter x: ");
 * 
 * @param state Current parser state containing tokens and position
 * @return StmtPtr Pointer to an InputStmt node
 * @throws runtime_error if the input statement syntax is invalid
 */
StmtPtr parseInput(ParserState &state)
{
  Token name = advance(state); // Get variable name
  consume(state, TokenType::ASSIGN, "Expected '=' after variable name");

  // Check for either READ token or 'r'
  if (!match(state, TokenType::READ) && peek(state).lexeme != "r")
  {
    throw runtime_error("Line " + to_string(peek(state).line) +
                        ": Expected 'r' after '='");
  }
  if (peek(state).lexeme == "r")
  {
    advance(state); // Consume 'r'
  }

  consume(state, TokenType::LPAREN, "Expected '(' after 'r'");

  // Expect a string literal for the prompt
  if (!match(state, TokenType::STRING))
  {
    throw runtime_error("Line " + to_string(peek(state).line) +
                        ": Expected string prompt in r statement");
  }
  Token prompt = previous(state);

  consume(state, TokenType::RPAREN, "Expected ')' after prompt");
  consume(state, TokenType::SEMICOLON, "Expected ';' after r statement");

  return make_shared<InputStmt>(name, prompt);
}


/**
 * @brief Parses a print statement in the form: print expression;
 * 
 * @param state Current parser state
 * @return StmtPtr Pointer to a PrintStmt node
 * @throws runtime_error if the print statement syntax is invalid
 */
StmtPtr parsePrint(ParserState &state)
{
  ExprPtr value = parseExpression(state);
  consume(state, TokenType::SEMICOLON, "Expected ';' after value");
  return make_shared<PrintStmt>(value);
}

/**
 * @brief Parses an if statement with optional else branch
 * 
 * Syntax: if (condition) statement [else statement]
 * 
 * @param state Current parser state
 * @return StmtPtr Pointer to an IfStmt node
 * @throws runtime_error if the if statement syntax is invalid
 */
StmtPtr parseIf(ParserState &state)
{
  consume(state, TokenType::LPAREN, "Expected '(' after 'if'");
  ExprPtr condition = parseComparison(state);
  consume(state, TokenType::RPAREN, "Expected ')' after if condition");

  StmtPtr thenBranch = parseStatement(state);
  StmtPtr elseBranch = nullptr;

  if (match(state, TokenType::ELSE))
  {
    elseBranch = parseStatement(state);
  }

  return make_shared<IfStmt>(condition, thenBranch, elseBranch);
}

/**
 * @brief Parses a while loop statement
 * 
 * Syntax: while (condition) statement
 * 
 * @param state Current parser state
 * @return StmtPtr Pointer to a WhileStmt node
 * @throws runtime_error if the while statement syntax is invalid
 */
StmtPtr parseWhile(ParserState &state)
{
  consume(state, TokenType::LPAREN, "Expected '(' after 'while'");
  ExprPtr condition = parseComparison(state);
  consume(state, TokenType::RPAREN, "Expected ')' after while condition");

  StmtPtr body = parseStatement(state);
  return make_shared<WhileStmt>(condition, body);
}

/**
 * @brief Parses an assignment statement
 * 
 * Syntax: identifier = expression;
 * 
 * @param state Current parser state
 * @return StmtPtr Pointer to an AssignmentStmt node
 * @throws runtime_error if the assignment syntax is invalid
 */
StmtPtr parseAssignment(ParserState &state)
{
  Token name = advance(state);
  consume(state, TokenType::ASSIGN, "Expected '=' after variable name");
  ExprPtr value = parseExpression(state);
  consume(state, TokenType::SEMICOLON, "Expected ';' after value");
  return make_shared<AssignmentStmt>(name, value);
}

/**
 * @brief Parses a comparison expression
 * 
 * Handles comparison operators: >, <, >=, <=, ==, !=
 * 
 * @param state Current parser state
 * @return ExprPtr Pointer to a BinaryExpr node for the comparison
 */
ExprPtr parseComparison(ParserState &state)
{
  ExprPtr expr = parseExpression(state);

  while (match(state, TokenType::GREATER) ||
         match(state, TokenType::GREATER_EQUAL) ||
         match(state, TokenType::LESS) ||
         match(state, TokenType::LESS_EQUAL) ||
         match(state, TokenType::EQUAL_EQUAL) ||
         match(state, TokenType::NOT_EQUAL))
  {
    Token op = previous(state);
    ExprPtr right = parseExpression(state);
    expr = make_shared<BinaryExpr>(expr, op, right);
  }

  return expr;
}

/**
 * @brief Helper function to consume an expected token
 * 
 * @param state Current parser state
 * @param type Expected token type
 * @param message Error message if token doesn't match
 * @throws runtime_error if the expected token is not found
 */
void consume(ParserState &state, TokenType type, const string &message)
{
  if (check(state, type))
  {
    advance(state);
    return;
  }
  throw runtime_error("Line " + to_string(peek(state).line) + ": " + message);
}

/**
 * @brief Parses a term (addition/subtraction)
 * 
 * Handles operators: +, -
 * Has lower precedence than multiplication/division
 * 
 * @param state Current parser state
 * @return ExprPtr Pointer to the resulting expression
 */
ExprPtr parseTerm(ParserState &state)
{
  ExprPtr expr = parseFactor(state);

  while (match(state, TokenType::PLUS) || match(state, TokenType::MINUS))
  {
    Token op = previous(state);
    ExprPtr right = parseFactor(state);
    expr = make_shared<BinaryExpr>(expr, op, right);
  }

  return expr;
}

/**
 * @brief Parses a factor (multiplication/division)
 * 
 * Handles operators: *, /
 * Has higher precedence than addition/subtraction
 * 
 * @param state Current parser state
 * @return ExprPtr Pointer to the resulting expression
 */
ExprPtr parseFactor(ParserState &state)
{
  ExprPtr expr = parsePrimary(state);

  while (match(state, TokenType::MULTIPLY) || match(state, TokenType::DIVIDE))
  {
    Token op = previous(state);
    ExprPtr right = parsePrimary(state);
    expr = make_shared<BinaryExpr>(expr, op, right);
  }

  return expr;
}

/**
 * @brief Parses a primary expression (literals, variables, or parenthesized expressions)
 * 
 * Primary expressions are the atomic building blocks of more complex expressions.
 * This function handles:
 * - Numeric literals (integers and doubles)
 * - String literals
 * - Boolean literals
 * - Variable references
 * - Parenthesized expressions
 * 
 * Grammar rule:
 * primary -> NUMBER | STRING | BOOLEAN | IDENTIFIER | '(' expression ')'
 * 
 * @param state Current parser state
 * @return ExprPtr Pointer to the parsed primary expression
 * @throws runtime_error if an invalid expression is encountered
 */
ExprPtr parsePrimary(ParserState &state)
{
  if (match(state, TokenType::INTEGER) ||
      match(state, TokenType::DOUBLE) ||
      match(state, TokenType::BOOLEAN))
  {
    return make_shared<LiteralExpr>(previous(state));
  }

  if (match(state, TokenType::STRING))
  {
    cout << "STRING" << endl;
    cout << previous(state).lexeme << endl;
    return make_shared<LiteralExpr>(previous(state));
  }

  if (match(state, TokenType::IDENTIFIER))
  {
    return make_shared<VariableExpr>(previous(state));
  }

  if (match(state, TokenType::LPAREN))
  {

    ExprPtr expr = parseExpression(state);
    consume(state, TokenType::RPAREN, "Expected ')' after expression");
    return expr;
  }

  throw runtime_error("Expected expression");
}

/**
 * @brief Parses an expression
 * 
 * This function handles expressions at the addition/subtraction level.
 * It follows the operator precedence by first parsing terms (multiplication/division)
 * and then handling any + or - operators.
 * 
 * Grammar rule:
 * expression -> term (('+' | '-') term)*
 * 
 * @param state Current parser state
 * @return ExprPtr Pointer to the parsed expression
 */
ExprPtr parseExpression(ParserState &state)
{
    ExprPtr expr = parseTerm(state);

    while (match(state, TokenType::PLUS) || match(state, TokenType::MINUS))
    {
        Token op = previous(state);
        ExprPtr right = parseTerm(state);
        expr = make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

/**
 * @brief Parses a type declaration statement with optional initialization
 * 
 * This function handles three forms of type declarations:
 * 1. Simple declaration: type identifier;
 * 2. Declaration with initialization: type identifier = expression;
 * 3. Declaration with input: type identifier = r("prompt");
 * 
 * Example valid declarations:
 * - int x;
 * - double y = 3.14;
 * - string name = r("Enter name: ");
 * 
 * @param state Current parser state
 * @return StmtPtr Pointer to TypeDeclarationStmt
 * @throws runtime_error if declaration syntax is invalid
 */
StmtPtr parseTypeDeclaration(ParserState &state)
{
    Token type = previous(state);
    Token name = advance(state);

    if (name.type != TokenType::IDENTIFIER)
    {
        throw runtime_error("Line " + to_string(peek(state).line) +
                            ": Expected variable name after type");
    }

    ExprPtr initializer = nullptr;
    if (match(state, TokenType::ASSIGN))
    {
        // Check if it's an input statement
        if (peek(state).type == TokenType::READ || peek(state).lexeme == "r")
        {
            // Create an InputStmt but wrap it in a TypeDeclarationStmt
            if (peek(state).lexeme == "r") {
                advance(state); // Consume 'r'
            } else {
                match(state, TokenType::READ); // Consume 'read'
            }

            consume(state, TokenType::LPAREN, "Expected '(' after 'r'");
            
            if (!match(state, TokenType::STRING))
            {
                throw runtime_error("Line " + to_string(peek(state).line) +
                                    ": Expected string prompt in r statement");
            }
            Token prompt = previous(state);
            
            consume(state, TokenType::RPAREN, "Expected ')' after prompt");
            consume(state, TokenType::SEMICOLON, "Expected ';' after r statement");

            // Create an InputStmt and store it
            auto inputStmt = make_shared<InputStmt>(name, prompt);
            
            // Return a TypeDeclarationStmt with the InputStmt
            return make_shared<TypeDeclarationStmt>(type, name, nullptr, inputStmt);
        }
        else
        {
            // Regular initialization
            initializer = parseExpression(state);
            consume(state, TokenType::SEMICOLON, "Expected ';' after declaration");
        }
    }
    else
    {
        consume(state, TokenType::SEMICOLON, "Expected ';' after declaration");
    }

    return make_shared<TypeDeclarationStmt>(type, name, initializer);
}