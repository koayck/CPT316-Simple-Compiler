/**
 * @file Parser.h
 * @brief Parser interface for MiniLang
 * 
 * This file defines the interface for the recursive descent parser that processes
 * tokens into an Abstract Syntax Tree (AST). The parser follows a top-down parsing
 * strategy where each grammar rule in the language has a corresponding parse function.
 * 
 * Key components:
 * - ParserState: Maintains the current parsing context and token stream
 * - Helper functions: For token manipulation and error handling
 * - Statement parsers: Functions to parse different types of statements
 * - Expression parsers: Functions implementing operator precedence parsing
 */

#pragma once
#include "Token.h"
#include "AST.h"
#include <vector>
#include <stdexcept>
#include <string>

/**
 * @brief Maintains the state of the parser during parsing
 * 
 * ParserState keeps track of the token stream and the current position
 * within that stream during parsing.
 */
struct ParserState
{
    const std::vector<Token> &tokens;  ///< Reference to the token stream
    size_t current;                    ///< Current position in the token stream

    ParserState(const std::vector<Token> &tokens) : tokens(tokens), current(0) {}
};

/**
 * @brief Main entry point for parsing
 * @param tokens Vector of tokens to parse
 * @return Vector of parsed statements as AST nodes
 */
std::vector<StmtPtr> parse(const std::vector<Token> &tokens);

// Token Stream Helper Functions

/**
 * @brief Checks if we've reached the end of the token stream
 */
bool isAtEnd(const ParserState &state);

/**
 * @brief Returns the current token without consuming it
 */
Token peek(const ParserState &state);

/**
 * @brief Looks ahead in the token stream by a specified number of tokens
 * @param lookahead Number of tokens to look ahead (default: 1)
 */
Token peekNext(const ParserState &state, int lookahead = 1);

/**
 * @brief Returns the previously consumed token
 */
Token previous(const ParserState &state);

/**
 * @brief Consumes and returns the current token
 */
Token advance(ParserState &state);

/**
 * @brief Checks if the current token is of the specified type
 */
bool check(const ParserState &state, TokenType type);

/**
 * @brief Consumes the current token if it matches the specified type
 * @return true if token was matched and consumed, false otherwise
 */
bool match(ParserState &state, TokenType type);

/**
 * @brief Consumes a token if it matches the expected type, throws error otherwise
 * @param message Error message to display if token type doesn't match
 * @throws std::runtime_error if the expected token type is not found
 */
void consume(ParserState &state, TokenType type, const std::string &message);

// Statement Parsing Functions

/**
 * @brief Parses any type of statement based on the current token
 * Dispatches to specific statement parsers based on the current token type
 */
StmtPtr parseStatement(ParserState &state);

/**
 * @brief Parses variable declarations with type annotations
 * Format: type identifier = expression
 */
StmtPtr parseTypeDeclaration(ParserState &state);

/**
 * @brief Parses assignment statements
 * Format: identifier = expression
 */
StmtPtr parseAssignment(ParserState &state);

/**
 * @brief Parses print statements
 * Format: print expression
 */
StmtPtr parsePrint(ParserState &state);

/**
 * @brief Parses input statements
 * Format: input identifier
 */
StmtPtr parseInput(ParserState &state);


/**
 * @brief Parses a block of statements enclosed in braces
 * Format: { statement* }
 */
StmtPtr parseBlock(ParserState &state);

/**
 * @brief Parses if statements with optional else clause
 * Format: if (condition) statement [else statement]
 */
StmtPtr parseIf(ParserState &state);

/**
 * @brief Parses while loops
 * Format: while (condition) statement
 */
StmtPtr parseWhile(ParserState &state);

// Expression Parsing Functions - Implementing Operator Precedence
/**
 * @brief Parses comparison expressions (<, >, <=, >=, ==, !=)
 * Lowest precedence level
 */
ExprPtr parseComparison(ParserState &state);

/**
 * @brief Parses arithmetic expressions (+ and -)
 */
ExprPtr parseExpression(ParserState &state);

/**
 * @brief Parses multiplication and division
 */
ExprPtr parseTerm(ParserState &state);

/**
 * @brief Parses unary operations and factors
 */
ExprPtr parseFactor(ParserState &state);

/**
 * @brief Parses exponentiation operations
 */
ExprPtr parsePower(ParserState &state);

/**
 * @brief Parses primary expressions (literals, identifiers, parenthesized expressions)
 * Highest precedence level
 */
ExprPtr parsePrimary(ParserState &state);

/**
 * @brief Creates an error message with line content and pointer
 */
string createErrorMessage(const ParserState &state, const std::string &message);
