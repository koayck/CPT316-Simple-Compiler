#include "Parser.h"
#include <iostream>
#include <memory>

using namespace std;

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

StmtPtr parseStatement(ParserState &state)
{
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
        match(state, TokenType::TYPE_STRING))
    {
      return parseTypeDeclaration(state);
    }
    if (peek(state).type == TokenType::IDENTIFIER &&
        peekNext(state).type == TokenType::ASSIGN)
    {
      if (peekNext(state, 2).type == TokenType::READ)
      {
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
    initializer = parseExpression(state);
  }

  consume(state, TokenType::SEMICOLON, "Expected ';' after declaration");
  return make_shared<TypeDeclarationStmt>(type, name, initializer);
}

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

void consume(ParserState &state, TokenType type, const string &message)
{
  if (check(state, type))
  {
    advance(state);
    return;
  }
  throw runtime_error("Line " + to_string(peek(state).line) + ": " + message);
}

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

StmtPtr parseWhile(ParserState &state)
{
  consume(state, TokenType::LPAREN, "Expected '(' after 'while'");
  ExprPtr condition = parseComparison(state);
  consume(state, TokenType::RPAREN, "Expected ')' after while condition");

  StmtPtr body = parseStatement(state);
  return make_shared<WhileStmt>(condition, body);
}

StmtPtr parsePrint(ParserState &state)
{
  ExprPtr value = parseExpression(state);
  consume(state, TokenType::SEMICOLON, "Expected ';' after value");
  return make_shared<PrintStmt>(value);
}

StmtPtr parseInput(ParserState &state)
{
  Token name = advance(state);
  consume(state, TokenType::ASSIGN, "Expected '=' after variable name");
  consume(state, TokenType::READ, "Expected 'read' after '='");
  consume(state, TokenType::SEMICOLON, "Expected ';' after 'read'");
  return make_shared<InputStmt>(name);
}

StmtPtr parseAssignment(ParserState &state)
{
  Token name = advance(state);
  consume(state, TokenType::ASSIGN, "Expected '=' after variable name");
  ExprPtr value = parseExpression(state);
  consume(state, TokenType::SEMICOLON, "Expected ';' after value");
  return make_shared<AssignmentStmt>(name, value);
}

ExprPtr parseExpression(ParserState &state)
{
  return parseTerm(state);
}

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

ExprPtr parsePrimary(ParserState &state)
{
  if (match(state, TokenType::INTEGER) || match(state, TokenType::DOUBLE))
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

  throw runtime_error("Expected expression");
}