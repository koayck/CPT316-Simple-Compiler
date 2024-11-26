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

  try {
    while (!isAtEnd(state)) {
        statements.push_back(parseStatement(state));
    }

    // Check for any unclosed delimiters at the end
    if (!state.delimiterStack.empty()) {
        Delimiter unclosed = state.delimiterStack.back();
        throw runtime_error("Line " + to_string(unclosed.line) + 
            ", Column " + to_string(unclosed.column) + 
            ": Unclosed " + tokenToString(unclosed.type));
    }
  } catch (const runtime_error& e) {
    throw;
  }

  return statements;
}

/**
 * @brief Helper functions for parsing
 */

/**
 * @brief Checks if we've reached the end of the token stream
 * @param state Current parser state containing tokens and position
 * @return true if current token is EOF_TOKEN, false otherwise
 */
bool isAtEnd(const ParserState &state) {
    return peek(state).type == TokenType::EOF_TOKEN;
}

/**
 * @brief Returns the current token without consuming it (moving forward)
 * @param state Current parser state
 * @return Token at current position
 */
Token peek(const ParserState &state) {
    return state.tokens[state.current];
}

/**
 * @brief Looks ahead in the token stream by a specified number of tokens
 * Useful for multi-token lookahead when parsing complex constructs
 * @param state Current parser state
 * @param lookahead Number of tokens to look ahead (default: 1)
 * @return Token at current position + lookahead
 */
Token peekNext(const ParserState &state, int lookahead) {
    return state.tokens[state.current + lookahead];
}

/**
 * @brief Returns the previously consumed token
 * Used after advancing to access the token we just processed
 * @param state Current parser state
 * @return Token at (current - 1) position
 */
Token previous(const ParserState &state) {
    return state.tokens[state.current - 1];
}

/**
 * @brief Consumes and returns the current token, advancing the position
 * Main method for moving through the token stream during parsing
 * @param state Current parser state
 * @return Token that was just consumed
 */
Token advance(ParserState &state) {
    if (!isAtEnd(state)) {
        state.current++;  // Move to next token if not at end
    }
    return previous(state);  // Return the token we just passed
}

/**
 * @brief Checks if the current token matches the expected type
 * Used for conditional parsing decisions without consuming the token
 * @param state Current parser state
 * @param type Expected token type
 * @return true if current token matches type, false otherwise
 */
bool check(const ParserState &state, TokenType type) {
    return !isAtEnd(state) && peek(state).type == type;
}

/**
 * @brief Tries to match and consume a token of the expected type
 * Combines check() and advance() for convenient token consumption
 * @param state Current parser state
 * @param type Expected token type
 * @return true if token was matched and consumed, false otherwise
 */
bool match(ParserState &state, TokenType type) {
    if (check(state, type)) {
        advance(state);
        return true;
    }
    return false;
}

/**
 * @brief Consumes a token if it matches the expected type, throws error otherwise
 * Used when a specific token is required by the grammar
 * @param state Current parser state
 * @param type Expected token type
 * @param message Error message if token doesn't match
 * @throws runtime_error with detailed error message if token type doesn't match
 */
void consume(ParserState &state, TokenType type, const string message) {
    if (check(state, type)) {
        advance(state);
        return;
    }
    throw runtime_error(createErrorMessage(state, message));
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
    try
    {
        Token current = peek(state);
        Token next = peekNext(state);

        // Check for invalid statement patterns
        if (current.type == TokenType::PLUS || current.type == TokenType::MINUS ||
            current.type == TokenType::MULTIPLY || current.type == TokenType::DIVIDE) {
            throw runtime_error(createErrorMessage(state, 
                "Invalid statement: cannot start with operator '" + current.lexeme + "'"));
        }

        // Check for consecutive identifiers
        if (current.type == TokenType::IDENTIFIER && next.type == TokenType::IDENTIFIER) {
            throw runtime_error(createErrorMessage(state, 
                "Invalid statement: unexpected identifier '" + next.lexeme + 
                "' after identifier '" + current.lexeme + "' - did you mean to use an operator?"));
        }

        // Check for invalid left-hand side of assignment
        if (current.type == TokenType::IDENTIFIER && next.type == TokenType::PLUS) {
            Token afterPlus = peekNext(state, 2);
            if (afterPlus.type == TokenType::IDENTIFIER || 
                afterPlus.type == TokenType::INTEGER || 
                afterPlus.type == TokenType::DOUBLE) {
                Token afterExpr = peekNext(state, 3);
                if (afterExpr.type == TokenType::ASSIGN) {
                    throw runtime_error(createErrorMessage(state, 
                        "Invalid assignment: left side must be a single identifier"));
                }
            }
        }

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
        if (peek(state).type == TokenType::IDENTIFIER)
        {
            if (peekNext(state).type == TokenType::ASSIGN)
            {
                if (peekNext(state, 2).type == TokenType::READ ||
                    peekNext(state, 2).lexeme == "r")
                {
                    return parseInput(state);
                }
                return parseAssignment(state);
            }
        }

        throw runtime_error(createErrorMessage(state, "Expected statement"));
    }
    catch (const runtime_error &e)
    {
        // Propagate the error with the correct line number
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
    throw runtime_error(createErrorMessage(state, "Expected 'r' after '='"));
  }
  if (peek(state).lexeme == "r")
  {
    advance(state); // Consume 'r'
  }

  consume(state, TokenType::LPAREN, "Expected '(' after 'r'");

  // Expect a string literal for the prompt
  if (!match(state, TokenType::STRING))
  {
    throw runtime_error(createErrorMessage(state, "Expected string prompt in r statement"));
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
 * @brief Parses a block of statements enclosed in braces
 *
 * Syntax: { statement* }
 *
 * @param state Current parser state
 * @return StmtPtr Pointer to a BlockStmt node
 * @throws runtime_error if the block syntax is invalid
 */
StmtPtr parseBlock(ParserState &state) {
    vector<StmtPtr> statements;
    
    Token openBrace = peek(state);
    if (!match(state, TokenType::LBRACE)) {
        consume(state, TokenType::LBRACE, "Expected '{' at start of block");
    }
    pushDelimiter(state, TokenType::LBRACE, openBrace.line, openBrace.column);
    
    while (!check(state, TokenType::RBRACE) && !isAtEnd(state)) {
        // Check for misplaced closing parenthesis
        if (check(state, TokenType::RPAREN)) {
            throw runtime_error(createErrorMessage(state, 
                "Unexpected ')' in block - did you mean '}'?"));
        }

        try {
            checkInvalidTokenSequence(state);
            statements.push_back(parseStatement(state));
        } catch (const runtime_error& e) {
            throw;
        }
    }
    
    if (check(state, TokenType::RBRACE)) {
        popDelimiter(state, TokenType::RBRACE, "block");
        advance(state);
    } else {
        if (!state.delimiterStack.empty()) {
            Delimiter unclosed = state.delimiterStack.back();
            throw runtime_error("Line " + to_string(unclosed.line) + 
                ", Column " + to_string(unclosed.column) + 
                ": Unclosed " + tokenToString(unclosed.type) + 
                " - missing closing '}'");
        }
    }
    
    return make_shared<BlockStmt>(statements);
}

/**
 * @brief Parses an if statement with optional else branch
 *
 * Syntax: if (condition) statement | { statements* } [else statement | { statements* }]
 *
 * @param state Current parser state
 * @return StmtPtr Pointer to an IfStmt node
 * @throws runtime_error if the if statement syntax is invalid
 */
StmtPtr parseIf(ParserState &state)
{
    Token openParen = peek(state);
    consume(state, TokenType::LPAREN, "Expected '(' after 'if'");
    pushDelimiter(state, TokenType::LPAREN, openParen.line, openParen.column);
    
    if (check(state, TokenType::RPAREN)) {
        throw runtime_error(createErrorMessage(state, 
            "Empty condition in if statement"));
    }
    
    ExprPtr condition = parseComparison(state);
    
    if (!check(state, TokenType::RPAREN)) {
        throw runtime_error(createErrorMessage(state, 
            "Missing closing ')' after if condition"));
    }
    
    consume(state, TokenType::RPAREN, "Expected ')' after if condition");
    popDelimiter(state, TokenType::RPAREN, "if condition");

    // Parse the then branch
    StmtPtr thenBranch;
    if (check(state, TokenType::LBRACE)) {
        // If we see a brace, parse as a block
        thenBranch = parseBlock(state);
    } else {
        // Otherwise parse a single statement
        thenBranch = parseStatement(state);
    }

    // Parse the optional else branch
    StmtPtr elseBranch = nullptr;
    if (match(state, TokenType::ELSE)) {
        if (check(state, TokenType::LBRACE)) {
            // If we see a brace, parse as a block
            elseBranch = parseBlock(state);
        } else {
            // Otherwise parse a single statement
            elseBranch = parseStatement(state);
        }
    }

    return make_shared<IfStmt>(condition, thenBranch, elseBranch);
}

/**
 * @brief Parses a while loop statement
 *
 * Syntax: while (condition) statement | { statements* }
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

    StmtPtr body;
    if (check(state, TokenType::LBRACE)) {
        // If we see a brace, parse as a block
        body = parseBlock(state);
    } else {
        // Otherwise parse a single statement
        body = parseStatement(state);
    }

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
    
    // Check for semicolon immediately after the expression
    if (!check(state, TokenType::SEMICOLON)) {
        throw runtime_error(createErrorMessage(state, "Expected ';' after value"));
    }
    
    consume(state, TokenType::SEMICOLON, "Expected ';' after value");
    return make_shared<AssignmentStmt>(name, value);
}

/**
 * @brief Parses a comparison expression
 * Handles comparison operators and logical operators (&&, ||)
 */
ExprPtr parseComparison(ParserState &state)
{
    ExprPtr expr = parseExpression(state);

    while (match(state, TokenType::GREATER) ||
           match(state, TokenType::GREATER_EQUAL) ||
           match(state, TokenType::LESS) ||
           match(state, TokenType::LESS_EQUAL) ||
           match(state, TokenType::EQUAL_EQUAL) ||
           match(state, TokenType::NOT_EQUAL) ||
           match(state, TokenType::AND) ||      // Add AND operator
           match(state, TokenType::OR))         // Add OR operator
    {
        Token op = previous(state);
        ExprPtr right = parseExpression(state);
        expr = make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
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
ExprPtr parseExpression(ParserState &state) {
    // Check for expression starting with binary operator
    Token next = peek(state);
    if (next.type == TokenType::PLUS || next.type == TokenType::MINUS ||
        next.type == TokenType::MULTIPLY || next.type == TokenType::DIVIDE) {
        throw runtime_error(createErrorMessage(state, 
            "Expression cannot start with operator '" + next.lexeme + "'"));
    }

    ExprPtr expr = parseTerm(state);

    while (match(state, TokenType::PLUS) || match(state, TokenType::MINUS)) {
        Token op = previous(state);
        
        // Check for missing right operand
        if (check(state, TokenType::SEMICOLON) || check(state, TokenType::RPAREN)) {
            throw runtime_error(createErrorMessage(state, 
                "Missing right operand after operator '" + op.lexeme + "'"));
        }

        ExprPtr right = parseTerm(state);
        expr = make_shared<BinaryExpr>(expr, op, right);
        
        checkInvalidTokenSequence(state);
    }

    return expr;
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

  throw runtime_error(createErrorMessage(state, "Expected expression"));
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

    // Check for valid identifier pattern (must start with letter or underscore)
    if (name.type != TokenType::IDENTIFIER) {
        // First check if it starts with a digit
        if (isdigit(name.lexeme[0])) {
            throw runtime_error(createErrorMessage(state, 
                "Invalid identifier: cannot start with a number"));
        }
        // Then check if it starts with letter or underscore
        if (!isalpha(name.lexeme[0]) && name.lexeme[0] != '_') {
            throw runtime_error(createErrorMessage(state, 
                "Invalid identifier: must start with a letter or underscore"));
        }
        // If we get here, it's some other invalid pattern
        throw runtime_error(createErrorMessage(state, 
            "Invalid identifier: '" + name.lexeme + "'"));
    }

    ExprPtr initializer = nullptr;
    if (match(state, TokenType::ASSIGN))
    {
        // Check if it's an input statement
        if (peek(state).type == TokenType::READ || peek(state).lexeme == "r")
        {
            // Create an InputStmt but wrap it in a TypeDeclarationStmt
            if (peek(state).lexeme == "r")
            {
                advance(state); // Consume 'r'
            }
            else
            {
                match(state, TokenType::READ); // Consume 'read'
            }

            consume(state, TokenType::LPAREN, "Expected '(' after 'r'");

            if (!match(state, TokenType::STRING))
            {
                throw runtime_error(createErrorMessage(state, "Expected string prompt in r statement"));
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
            // Regular initialization - use parseComparison instead of parseExpression
            // to handle logical operators
            initializer = parseComparison(state);
            consume(state, TokenType::SEMICOLON, "Expected ';' after declaration");
        }
    }
    else
    {
        consume(state, TokenType::SEMICOLON, "Expected ';' after declaration");
    }

    return make_shared<TypeDeclarationStmt>(type, name, initializer);
}


/**
 * @brief Creates and returns a string representation of the AST
 *
 * This function recursively traverses the AST and builds a formatted string
 * representation with proper indentation for visualization.
 *
 * @param stmt The statement node to process
 * @param indent Current indentation level
 * @return string The formatted string representation of the AST
 */
string createASTString(const StmtPtr &stmt, int indent = 0)
{
    if (!stmt) return "";
    
    // Add indentation to each line of the statement's string representation
    std::string stmtStr = stmt->toString();
    std::string indentation(indent, ' ');
    
    size_t pos = 0;
    while ((pos = stmtStr.find('\n', pos)) != std::string::npos) {
        stmtStr.insert(pos + 1, indentation);
        pos += indentation.length() + 1;
    }
    
    return indentation + stmtStr;
}

/**
 * @brief Creates a string representation of the entire AST
 *
 * @param statements Vector of statement nodes
 * @return string The formatted string representation of the complete AST
 */
string createCompleteASTString(const vector<StmtPtr> &statements)
{
    string result = "\n=== Abstract Syntax Tree ===\n";
    result += "Program\n";
    result += "|-- Statements:\n";
    
    for (const auto &statement : statements)
    {
        result += createASTString(statement, 4);
    }
    return result;
}

/**
 * @brief Creates an error message with line content and pointer
 *
 * @param state Current parser state
 * @param message Error message
 * @return string Error message with line content and pointer
 */
string createErrorMessage(const ParserState &state, const string message) {
    Token currentToken = peek(state);
    int line = currentToken.line;
    int column = currentToken.column;
    
    // Find the line content
    string lineContent;
    int currentLine = 1;
    size_t pos = 0;
    while (pos < state.tokens[0].lexeme.length() && currentLine < line) {
        if (state.tokens[0].lexeme[pos] == '\n') currentLine++;
        pos++;
    }
    size_t lineStart = pos;
    while (pos < state.tokens[0].lexeme.length() && state.tokens[0].lexeme[pos] != '\n') {
        lineContent += state.tokens[0].lexeme[pos++];
    }

    // Create the error message with line content and pointer
    string errorMsg = "Line " + to_string(line) + ", Column " + to_string(column) + ": " + message + "\n";
    errorMsg += lineContent + "\n";
    errorMsg += string(column - 1, ' ') + "^";
    
    return errorMsg;
}

// Add these helper functions to Parser.cpp
void pushDelimiter(ParserState& state, TokenType type, int line, int column) {
    Delimiter delim{type, line, column};
    state.delimiterStack.push_back(delim);
}

void popDelimiter(ParserState& state, TokenType expectedClosing, const string& context) {
    if (state.delimiterStack.empty()) {
        throw runtime_error(createErrorMessage(state, 
            "Unexpected closing " + tokenToString(expectedClosing) + " in " + context));
    }

    Delimiter opening = state.delimiterStack.back();
    state.delimiterStack.pop_back();

    // Check if the delimiters match
    if ((opening.type == TokenType::LPAREN && expectedClosing != TokenType::RPAREN) ||
        (opening.type == TokenType::LBRACE && expectedClosing != TokenType::RBRACE)) {
        throw runtime_error(createErrorMessage(state, 
            "Mismatched delimiters: expected closing " + 
            tokenToString(opening.type) + " from line " + 
            to_string(opening.line) + ", column " + 
            to_string(opening.column)));
    }
}

// Add helper function to convert TokenType to string
string tokenToString(TokenType type) {
    switch (type) {
        case TokenType::LPAREN: return "'('";
        case TokenType::RPAREN: return "')'";
        case TokenType::LBRACE: return "'{'";
        case TokenType::RBRACE: return "'}'";
        default: return tokenTypeToString(type);  // Use existing function for other types
    }
}

void checkInvalidTokenSequence(ParserState& state) {
    Token current = peek(state);
    Token next = peekNext(state);

    // Check for invalid token sequences
    if (current.type == TokenType::IDENTIFIER && next.type == TokenType::IDENTIFIER) {
        throw runtime_error(createErrorMessage(state, 
            "Unexpected identifier '" + next.lexeme + "' after identifier '" + current.lexeme + "'"));
    }

    // Check for expression on left side of assignment
    if (current.type == TokenType::IDENTIFIER && next.type == TokenType::PLUS) {
        Token nextNext = peekNext(state, 2);
        if (nextNext.type == TokenType::IDENTIFIER && 
            peekNext(state, 3).type == TokenType::ASSIGN) {
            throw runtime_error(createErrorMessage(state, 
                "Invalid assignment: expression cannot appear on left side of '='"));
        }
    }

    // Check for invalid operator sequences
    bool currentIsOperator = (current.type == TokenType::PLUS || current.type == TokenType::MINUS ||
                            current.type == TokenType::MULTIPLY || current.type == TokenType::DIVIDE);
    bool nextIsOperator = (next.type == TokenType::PLUS || next.type == TokenType::MINUS ||
                          next.type == TokenType::MULTIPLY || next.type == TokenType::DIVIDE);
    
    if (currentIsOperator && nextIsOperator) {
        throw runtime_error(createErrorMessage(state, 
            "Invalid operator sequence: unexpected '" + next.lexeme + "' after '" + current.lexeme + "'"));
    }

    // Check for invalid sequences with parentheses
    if (current.type == TokenType::RPAREN && next.type == TokenType::LPAREN) {
        throw runtime_error(createErrorMessage(state, 
            "Invalid expression: missing operator between ')' and '('"));
    }

    // Check for invalid sequences with operators
    if (currentIsOperator && (next.type == TokenType::SEMICOLON || 
                             next.type == TokenType::RPAREN)) {
        throw runtime_error(createErrorMessage(state, 
            "Invalid expression: operator '" + current.lexeme + "' missing right operand"));
    }
}