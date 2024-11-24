/**
 * @file Lexer.cpp
 * @brief Implementation of the lexical analyzer for MiniLang
 * 
 * This file implements the lexical analysis phase of the compiler.
 * Key features:
 * 1. Token recognition and creation
 * 2. Keyword handling
 * 3. Number literal parsing (integer and double)
 * 4. String literal parsing
 * 5. Identifier recognition
 * 6. Error handling with line numbers
 * 
 * The lexer processes the input character by character and groups them into tokens
 * according to the language specification.
 */

#include "Lexer.h"
#include <unordered_map>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

static const unordered_map<string, TokenType> keywords = {
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"int", TokenType::TYPE_INT},
    {"double", TokenType::TYPE_DOUBLE},
    {"string", TokenType::TYPE_STRING},
    {"bool", TokenType::TYPE_BOOL},
    {"true", TokenType::BOOLEAN},
    {"false", TokenType::BOOLEAN}
};

// tokenizes the source code and returns a vector of tokens
vector<Token> Lexer::tokenize()
{
    vector<Token> tokens;

    while (!isAtEnd())
    {
        start = current;
        Token token = scanToken();
        if (token.type != TokenType::INVALID)
        {
            tokens.push_back(token);
        }
    }

    tokens.push_back(Token(TokenType::EOF_TOKEN, "", line, current + 1));
    return tokens;
}

Token Lexer::number()
{
    bool isDouble = false;

    while (isDigit(peek()))
        advance();

    // Look for a fractional part
    if (peek() == '.' && isDigit(peekNext()))
    {
        isDouble = true;
        advance(); // Consume the "."

        while (isDigit(peek()))
            advance();
    }

    std::string numStr = source.substr(start, current - start);

    if (isDouble)
    {
        double value = std::stod(numStr);
        return Token(TokenType::DOUBLE, numStr, value, line, start + 1);
    }
    else
    {
        int value = std::stoi(numStr);
        return Token(TokenType::INTEGER, numStr, value, line, start + 1);
    }
}

Token Lexer::identifier()
{
    while (isAlphaNumeric(peek()))
        advance();

    std::string text = source.substr(start, current - start);

    // Check if it's a keyword
    auto it = keywords.find(text);

    if (it != keywords.end()) {
        if (text == "true" || text == "false") {
            return Token(TokenType::BOOLEAN, text, text == "true" ? 1.0 : 0.0, line, start + 1);
        }
        return makeToken(it->second);
    }

    return makeToken(TokenType::IDENTIFIER);
}

bool Lexer::match(char expected)
{
    if (isAtEnd() || source[current] != expected)
        return false;
    current++;
    return true;
}

Token Lexer::scanToken()
{
    skipWhitespace();
    start = current;

    if (isAtEnd())
        return makeToken(TokenType::EOF_TOKEN);

    char c = advance();

    switch (c)
    {
    case '(':
        return makeToken(TokenType::LPAREN);
    case ')':
        return makeToken(TokenType::RPAREN);
    case '{':
        return makeToken(TokenType::LBRACE);
    case '}':
        return makeToken(TokenType::RBRACE);
    case ';':
        return makeToken(TokenType::SEMICOLON);
    case '+':
        return makeToken(TokenType::PLUS);
    case '-':
        return makeToken(TokenType::MINUS);
    case '*':
        if (match('*'))
            return makeToken(TokenType::POWER);
        return makeToken(TokenType::MULTIPLY);
    case '/':
        return makeToken(TokenType::DIVIDE);
    case '=':
        if (match('='))
            return makeToken(TokenType::EQUAL_EQUAL);
        return makeToken(TokenType::ASSIGN);
    case '<':
        if (match('='))
            return makeToken(TokenType::LESS_EQUAL);
        return makeToken(TokenType::LESS);
    case '>':
        if (match('='))
            return makeToken(TokenType::GREATER_EQUAL);
        return makeToken(TokenType::GREATER);
    case '!':
        if (match('='))
            return makeToken(TokenType::NOT_EQUAL);
        return makeToken(TokenType::NOT);
    case '&':
        if (match('&'))
            return makeToken(TokenType::AND);
        break;
    case '|':
        if (match('|'))
            return makeToken(TokenType::OR);
        break;
    case '"':
        return string();
    case 'p':
        if (peek() == '(')
            return makeToken(TokenType::PRINT);
        break;
    case 'r':
        if (peek() == '(')
            return makeToken(TokenType::READ);
        return identifier();
    }

    if (isDigit(c))
    {
        return number();
    }
    if (isAlpha(c))
    {
        return identifier();
    }

    return makeToken(TokenType::INVALID);
}

void Lexer::skipWhitespace()
{
    while (true)
    {
        char c = peek();
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
            line++;
            advance();
            break;
        case '#':
            while (peek() != '\n' && !isAtEnd())
                advance();
            break;
        default:
            return;
        }
    }
}

Token Lexer::makeToken(TokenType type) const
{
    std::string text = source.substr(start, current - start);
    return Token(type, text, line, start + 1);
}

Token Lexer::makeToken(TokenType type, double value) const
{
    std::string text = source.substr(start, current - start);
    return Token(type, text, value, line, start + 1);
}

Token Lexer::string()
{
    // Skip the opening quote
    start = current; // Start after the opening quote

    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            line++;
        advance();
    }

    if (isAtEnd())
    {
        return makeToken(TokenType::INVALID); // Unterminated string
    }

    std::string value = source.substr(start, current - start);
    advance(); // Skip the closing quote

    return Token(TokenType::STRING, value, line, start + 1);
}

#include "Token.h"

string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::IF:
        return "IF";
    case TokenType::ELSE:
        return "ELSE";
    case TokenType::WHILE:
        return "WHILE";
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::MULTIPLY:
        return "MULTIPLY";
    case TokenType::DIVIDE:
        return "DIVIDE";
    case TokenType::POWER:
        return "POWER";
    case TokenType::ASSIGN:
        return "ASSIGN";
    case TokenType::GREATER:
        return "GREATER";
    case TokenType::LESS:
        return "LESS";
    case TokenType::GREATER_EQUAL:
        return "GREATER_EQUAL";
    case TokenType::LESS_EQUAL:
        return "LESS_EQUAL";
    case TokenType::EQUAL_EQUAL:
        return "EQUAL_EQUAL";
    case TokenType::NOT_EQUAL:
        return "NOT_EQUAL";
    case TokenType::AND:
        return "AND";
    case TokenType::OR:
        return "OR";
    case TokenType::NOT:
        return "NOT";
    case TokenType::LPAREN:
        return "LPAREN";
    case TokenType::RPAREN:
        return "RPAREN";
    case TokenType::LBRACE:
        return "LBRACE";
    case TokenType::RBRACE:
        return "RBRACE";
    case TokenType::SEMICOLON:
        return "SEMICOLON";
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::INTEGER:
        return "INTEGER";
    case TokenType::DOUBLE:
        return "DOUBLE";
    case TokenType::STRING:
        return "STRING";
    case TokenType::PRINT:
        return "PRINT";
    case TokenType::READ:
        return "READ";
    case TokenType::EOF_TOKEN:
        return "EOF_TOKEN";
    case TokenType::INVALID:
        return "INVALID";
    case TokenType::TYPE_INT:
        return "TYPE_INT";
    case TokenType::TYPE_DOUBLE:
        return "TYPE_DOUBLE";
    case TokenType::TYPE_STRING:
        return "TYPE_STRING";
    case TokenType::TYPE_BOOL:
        return "TYPE_BOOL";
    case TokenType::BOOLEAN:
        return "BOOLEAN";
    default:
        return "UNKNOWN"; // Fallback for any unrecognized type
    }
}

void printTokens(const vector<Token>& tokens) {
    // Print header
    cout << "\nTokenization Results:\n";
    cout << setw(8) << "Line" << setw(8) << "Column" << setw(16) << "Type" << setw(20) << "Value\n";
    cout << string(52, '-') << "\n";
    
    // Print each token
    for (const auto& token : tokens) {
        cout << setw(8) << token.line 
             << setw(8) << token.column 
             << setw(16) << tokenTypeToString(token.type);
             
        // Handle value based on token type
        if (token.type == TokenType::INTEGER || token.type == TokenType::DOUBLE) {
            cout << setw(20) << token.numValue;
        } else if (token.type == TokenType::STRING) {
            cout << setw(20) << "\"" + token.lexeme + "\"";
        } else {
            cout << setw(20) << token.lexeme;
        }
        cout << "\n";
    }
    cout << "\n";
}