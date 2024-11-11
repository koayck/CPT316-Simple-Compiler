#pragma once
#include <string>
#include <iostream>

enum class TokenType {
    // Keywords
    IF,
    ELSE,
    WHILE,
    
    // Data Types
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    
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
    
    // Special
    PRINT,  // 'p'
    READ,   // 'r'
    EOF_TOKEN,
    INVALID
};

// Forward declaration of the function
std::string tokenTypeToString(TokenType type);

struct Token {
    TokenType type;
    std::string lexeme;
    double numValue;  // Used for INTEGER and DOUBLE tokens
    int line;        // Add line number to Token
    
    // constructor
    // creates a new token with the given type and lexeme
    Token(TokenType t, const std::string& l, int ln) 
        : type(t), lexeme(l), numValue(0.0), line(ln) {}

    // creates a new token with the given type, lexeme, and number value
    Token(TokenType t, const std::string& l, double v, int ln) 
        : type(t), lexeme(l), numValue(v), line(ln) {}

    // Add stream operator as a friend function
    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << "Token{type=" << tokenTypeToString(token.type) 
           << ", lexeme='" << token.lexeme 
           << "', line=" << token.line << "}";
        return os;
    }
}; 