/**
 * @file Lexer.h
 * @brief Lexical analyzer interface for MiniLang
 * 
 * This file defines the Lexer class which performs lexical analysis (tokenization).
 * The lexer converts source code text into a sequence of tokens by:
 * - Identifying keywords, operators, and literals
 * - Handling whitespace and comments
 * - Tracking line numbers for error reporting
 * - Managing source code position
 */

#pragma once
#include "Token.h"
#include <string>
#include <vector>

// defines the Lexer class, which is responsible for tokenizing the source code
class Lexer
{
public:
    // constructor
    // explicit keyword is used to prevent implicit conversions
    // e.g. Lexer l = "source code"; is not allowed
    // instead, Lexer l("source code"); is required
    explicit Lexer(const std::string &source) : source(source), current(0), start(0), line(1) {}

    // tokenizes the source code and returns a vector of tokens
    std::vector<Token> tokenize();

private:
    std::string source; // the source code to be tokenized
    size_t current;     // the current position in the source code
    size_t start;       // the start position of the current token
    int line;           // the current line number

    // returns true if the current position is at the end of the source code
    bool isAtEnd() const { return current >= source.length(); }

    // returns the current character and advances the position by one
    char advance() { return source[current++]; }

    // returns the current character without advancing the position
    char peek() const { return isAtEnd() ? '\0' : source[current]; }

    // returns the next character without advancing the position
    char peekNext() const { return (current + 1 >= source.length()) ? '\0' : source[current + 1]; }

    // checks if the current character matches the expected character
    bool match(char expected);

    // scans the next token from the source code
    Token scanToken();

    // creates a new token with the given type
    Token makeToken(TokenType type) const;

    // creates a new token with the given type and value
    Token makeToken(TokenType type, double value) const;

    Token string();
    Token number();
    Token identifier();

    static bool isDigit(char c) { return c >= '0' && c <= '9'; }
    static bool isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; }
    static bool isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }
    void skipWhitespace();
};