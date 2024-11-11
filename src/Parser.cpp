#include "Parser.h"
#include <iostream>

using namespace std;

vector<StmtPtr> Parser::parse()
{
  vector<StmtPtr> statements;
  while (!isAtEnd())
  {
    statements.push_back(statement());
  }
  return statements;
}

// check if the current token is the end of the file
bool Parser::isAtEnd() const
{
  return peek().type == TokenType::EOF_TOKEN;
}

// get the current token
Token Parser::peek() const
{
  return tokens[current];
}

// get the next token
Token Parser::peekNext(int lookahead) const
{
  return tokens[current + lookahead];
}

// get the previous token
Token Parser::previous() const
{
  return tokens[current - 1];
}

// return the current token, then advance to the next token
Token Parser::advance()
{
  if (!isAtEnd())
    current++;
  return previous();
}

// check if the current token is of a certain type
bool Parser::check(TokenType type) const
{
  return !isAtEnd() && peek().type == type;
}

// check if the current token matches a certain type, then advance to the next token if it does
bool Parser::match(TokenType type)
{
  cout << "Attempting to match: " << tokenTypeToString(type)
       << " with current token: " << peek() << endl;
  if (check(type))
  {
    advance();
    return true;
  }
  return false;
}

// parse a statement
StmtPtr Parser::statement()
{
  try
  {
    if (match(TokenType::IF))
    {
      return ifStatement();
    }
    if (match(TokenType::WHILE))
    {
      return whileStatement();
    }
    if (match(TokenType::PRINT))
    {
      return printStatement();
    }
    if (match(TokenType::TYPE_INT) || match(TokenType::TYPE_DOUBLE) || match(TokenType::TYPE_STRING))
    {
      return typeDeclarationStatement();
    }
    if (peek().type == TokenType::IDENTIFIER && peekNext().type == TokenType::ASSIGN)
    {
      if (peekNext(2).type == TokenType::READ)
      {
        return inputStatement();
      }
      return assignmentStatement();
    }

    throw runtime_error("Expected statement");
  }
  catch (const runtime_error &e)
  {
    if (string(e.what()).find("Line") == string::npos)
    {
      throw runtime_error("Line " + to_string(peek().line) + ": " + e.what());
    }
    throw;
  }
}

// parse a type declaration statement
StmtPtr Parser::typeDeclarationStatement()
{
  Token type = previous(); // Get the type token (int, double, string)
  Token name = advance();  // Get the variable name

  if (name.type != TokenType::IDENTIFIER)
  {
    throw runtime_error("Line " + to_string(peek().line) + ": Expected variable name after type");
  }

  ExprPtr initializer = nullptr;
  if (match(TokenType::ASSIGN))
  {
    // Handle initialization
    initializer = expression();
  }

  consume(TokenType::SEMICOLON, "Expected ';' after declaration");

  return make_shared<TypeDeclarationStmt>(type, name, initializer);
}

// parse an assignment statement
StmtPtr Parser::assignmentStatement()
{
  Token name = advance(); // Get identifier
  consume(TokenType::ASSIGN, "Expected '=' after variable name");
  ExprPtr value = expression();
  consume(TokenType::SEMICOLON, "Expected ';' after assignment");
  return make_shared<AssignmentStmt>(name, value);
}

// parse a print statement
StmtPtr Parser::printStatement()
{
  consume(TokenType::LPAREN, "Expected '(' after 'p'");

  // Create a PrintStmt that can handle either a string literal or a variable
  Token printArg = advance(); // Get the argument token

  if (printArg.type != TokenType::STRING && printArg.type != TokenType::IDENTIFIER)
  {
    throw runtime_error("Expected string literal or variable in print statement");
  }

  consume(TokenType::RPAREN, "Expected ')' after print argument");
  consume(TokenType::SEMICOLON, "Expected ';' after print statement");

  return make_shared<PrintStmt>(printArg);
}

// parse an input statement
StmtPtr Parser::inputStatement()
{
  Token name = advance(); // Get identifier
  consume(TokenType::ASSIGN, "Expected '=' after variable name");
  consume(TokenType::READ, "Expected 'r' for input");
  consume(TokenType::LPAREN, "Expected '(' after 'r'");
  Token prompt = advance(); // Get prompt string
  if (prompt.type != TokenType::STRING)
  {
    throw runtime_error("Expected string literal in input statement");
  }
  consume(TokenType::RPAREN, "Expected ')' after prompt");
  consume(TokenType::SEMICOLON, "Expected ';' after input statement");
  return make_shared<InputStmt>(name, prompt);
}

// parse an if statement
StmtPtr Parser::ifStatement()
{
  ExprPtr condition = comparison();
  consume(TokenType::LBRACE, "Expected '{' after if condition");

  vector<StmtPtr> thenBranch;
  while (!check(TokenType::RBRACE) && !isAtEnd())
  {
    thenBranch.push_back(statement());
  }
  consume(TokenType::RBRACE, "Expected '}' after then branch");

  vector<StmtPtr> elseBranch;
  if (match(TokenType::ELSE))
  {
    consume(TokenType::LBRACE, "Expected '{' after else");
    while (!check(TokenType::RBRACE) && !isAtEnd())
    {
      elseBranch.push_back(statement());
    }
    consume(TokenType::RBRACE, "Expected '}' after else branch");
  }

  return make_shared<IfStmt>(condition, thenBranch, elseBranch);
}

// parse a while statement
StmtPtr Parser::whileStatement()
{
  ExprPtr condition = comparison();
  consume(TokenType::LBRACE, "Expected '{' after while condition");

  vector<StmtPtr> body;
  while (!check(TokenType::RBRACE) && !isAtEnd())
  {
    body.push_back(statement());
  }
  consume(TokenType::RBRACE, "Expected '}' after while body");

  return make_shared<WhileStmt>(condition, body);
}

// Parsing Expressions
// parse mathematical expressions, handling operator precedence from low to high: addition/subtraction, multiplication/division, and exponentiation.

// Add this new function to handle comparison expressions
ExprPtr Parser::comparison()
{
  ExprPtr expr = expression();

  while (match(TokenType::GREATER) || match(TokenType::GREATER_EQUAL) ||
         match(TokenType::LESS) || match(TokenType::LESS_EQUAL) ||
         match(TokenType::EQUAL_EQUAL) || match(TokenType::NOT_EQUAL))
  {
    Token op = previous();
    ExprPtr right = expression();
    expr = make_shared<BinaryExpr>(expr, op, right);
  }

  return expr;
}

// Parses addition and subtraction
ExprPtr Parser::expression()
{
  ExprPtr expr = term();

  while (match(TokenType::PLUS) || match(TokenType::MINUS))
  {
    Token op = previous();
    ExprPtr right = term();
    expr = make_shared<BinaryExpr>(expr, op, right);
  }

  return expr;
}

// Parses multiplication and division
ExprPtr Parser::term()
{
  ExprPtr expr = factor();

  while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE))
  {
    Token op = previous();
    ExprPtr right = factor();
    expr = make_shared<BinaryExpr>(expr, op, right);
  }

  return expr;
}

// Parses exponentiation
ExprPtr Parser::factor()
{
  ExprPtr expr = power();

  while (match(TokenType::POWER))
  {
    Token op = previous();
    ExprPtr right = power();
    expr = make_shared<BinaryExpr>(expr, op, right);
  }

  return expr;
}

// Prepares the parser for the highest-precedence expressions (literal values, variables)
ExprPtr Parser::power()
{
  return primary();
}

// Handles literal values, variables, and grouped expressions
ExprPtr Parser::primary()
{
  try
  {
    if (match(TokenType::INTEGER) || match(TokenType::DOUBLE))
    {
      return make_shared<LiteralExpr>(previous());
    }

    if (match(TokenType::IDENTIFIER))
    {
      return make_shared<VariableExpr>(previous());
    }

    if (match(TokenType::LPAREN))
    {
      ExprPtr expr = comparison();
      consume(TokenType::RPAREN, "Expected ')' after expression");
      return expr;
    }

    throw runtime_error("Expected expression");
  }
  catch (const runtime_error &e)
  {
    if (string(e.what()).find("Line") == string::npos)
    {
      throw runtime_error("Line " + to_string(peek().line) + ": " + e.what());
    }
    throw;
  }
}

// consume (return) current token of correct type, then advance to next token
void Parser::consume(TokenType type, const string &message)
{
  if (check(type))
  {
    advance();
    return;
  }
  throw runtime_error("Line " + to_string(peek().line) + ": " + message);
}