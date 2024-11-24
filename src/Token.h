/**
 * @file Token.h
 * @brief Token definitions and handling for MiniLang
 * 
 * This file defines the token types and token structure used in lexical analysis.
 * It includes:
 * - Token type enumeration (keywords, operators, literals, etc.)
 * - Token structure (type, lexeme, value, line number)
 * - String conversion utilities for tokens
 */

#pragma once
#include <string>
#include <iostream>

enum class TokenType
{
    // Keywords
    IF,
    ELSE,
    WHILE,

    // Data Types
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_BOOL,

    // Operators
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    POWER,
    ASSIGN,

    // Relational operators
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL,
    EQUAL_EQUAL,
    NOT_EQUAL,

    // Logical operators
    AND,
    OR,
    NOT,

    // Delimiters
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    SEMICOLON,

    // Literals
    IDENTIFIER,
    INTEGER,
    DOUBLE,
    STRING,
    BOOLEAN,

    // Special
    PRINT, // 'p'
    READ,  // 'r'
    EOF_TOKEN,
    INVALID
};

// Forward declaration of the function
std::string tokenTypeToString(TokenType type);

struct Token
{
    TokenType type;
    std::string lexeme;
    double numValue; // Used for INTEGER and DOUBLE tokens
    int line;        // Add line number to Token
    int column;      // Add column position
    std::string errorMessage;  // New field

    // constructor
    // creates a new token with the given type and lexeme
    Token(TokenType t, const std::string &l, int ln, int col)
        : type(t), lexeme(l), numValue(0.0), line(ln), column(col) {}

    // creates a new token with the given type, lexeme, and number value
    Token(TokenType t, const std::string &l, double v, int ln, int col)
        : type(t), lexeme(l), numValue(v), line(ln), column(col) {}

    // Add constructor overload for invalid tokens with error messages
    Token(TokenType type, const std::string& lexeme, int line, int column, const std::string& error = "")
        : type(type), lexeme(lexeme), numValue(0), line(line), column(column), errorMessage(error) {}

    // Add stream operator as a friend function
    friend std::ostream &operator<<(std::ostream &os, const Token &token)
    {
        os << "Token{type=" << tokenTypeToString(token.type)
           << ", lexeme='" << token.lexeme
           << "', line=" << token.line << ", column=" << token.column << "}";
        return os;
    }
};