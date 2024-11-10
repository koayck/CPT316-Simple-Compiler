#include "Parser.h"

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
  Token string = advance(); // Get string literal
  if (string.type != TokenType::STRING)
  {
    throw runtime_error("Expected string literal in print statement");
  }
  consume(TokenType::RPAREN, "Expected ')' after string");
  consume(TokenType::SEMICOLON, "Expected ';' after print statement");
  return make_shared<PrintStmt>(string);
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
  ExprPtr condition = expression();
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
  ExprPtr condition = expression();
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
    ExprPtr expr = expression();
    consume(TokenType::RPAREN, "Expected ')' after expression");
    return expr;
  }

  throw runtime_error("Expected expression");
}

// consume (return) current token of correct type, then advance to next token
void Parser::consume(TokenType type, const string &message)
{
  if (check(type))
  {
    advance();
    return;
  }
  throw runtime_error(message);
}