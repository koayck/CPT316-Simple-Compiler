/**
 * @file Parser.h
 * @brief Parser interface for MiniLang
 * 
 * This file defines the interface for the recursive descent parser.
 * It includes:
 * 1. Parser state management
 * 2. Function declarations for parsing different language constructs
 * 3. Helper function declarations for token handling
 * 
 * The parser implements a top-down parsing strategy, with separate functions
 * for each grammar rule in the language.
 */

#pragma once
#include "Token.h"
#include "AST.h"
#include <vector>
#include <stdexcept>
#include <string>

// Parser state structure
struct ParserState
{
    const std::vector<Token> &tokens;
    size_t current;

    // Constructor
    ParserState(const std::vector<Token> &tokens) : tokens(tokens), current(0) {}
};

// Main parsing function
std::vector<StmtPtr> parse(const std::vector<Token> &tokens);

// Helper functions
bool isAtEnd(const ParserState &state);
Token peek(const ParserState &state);
Token peekNext(const ParserState &state, int lookahead = 1);
Token previous(const ParserState &state);
Token advance(ParserState &state);
bool check(const ParserState &state, TokenType type);
bool match(ParserState &state, TokenType type);
void consume(ParserState &state, TokenType type, const std::string &message);

// Statement parsing functions
StmtPtr parseStatement(ParserState &state);
StmtPtr parseTypeDeclaration(ParserState &state);
StmtPtr parseAssignment(ParserState &state);
StmtPtr parsePrint(ParserState &state);
StmtPtr parseInput(ParserState &state);
StmtPtr parseIf(ParserState &state);
StmtPtr parseWhile(ParserState &state);

// Expression parsing functions
ExprPtr parseComparison(ParserState &state);
ExprPtr parseExpression(ParserState &state);
ExprPtr parseTerm(ParserState &state);
ExprPtr parseFactor(ParserState &state);
ExprPtr parsePower(ParserState &state);
ExprPtr parsePrimary(ParserState &state);