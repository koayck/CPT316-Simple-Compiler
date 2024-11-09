#pragma once
#include <string>

using namespace std;

enum class TokenType {
    // Keywords
    IF,
    ELSE,
    WHILE,
    
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

struct Token {
    TokenType type;
    string lexeme;
    double numValue;  // Used for INTEGER and DOUBLE tokens
    
    // constructor
    // creates a new token with the given type and lexeme
    Token(TokenType t, const string& l) : type(t), lexeme(l), numValue(0.0) {}

    // creates a new token with the given type, lexeme, and number value
    Token(TokenType t, const string& l, double v) : type(t), lexeme(l), numValue(v) {}
}; 