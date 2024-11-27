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
#include <algorithm>

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
    {"false", TokenType::BOOLEAN}};

// tokenizes the source code and returns a vector of tokens
vector<Token> Lexer::tokenize()
{
    vector<Token> tokens;

    while (!isAtEnd())
    {
        start = current;
        Token token = scanToken();
        if (token.type != TokenType::EOF_TOKEN)
        {
            tokens.push_back(token);
        }
    }

    // Add EOF token at column 1
    tokens.push_back(Token(TokenType::EOF_TOKEN, std::string(""), line, 1, ""));
    return tokens;
}

Token Lexer::number()
{
    int startColumn = column;
    size_t numberStart = current;

    // Parse the integer part
    while (isDigit(peek()))
    {
        advance();
        column++;
    }

    // Parse the decimal part if present
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance(); // consume the dot
        column++;

        while (isDigit(peek()))
        {
            advance();
            column++;
        }
    }

    // Get the number string and check if we're at an operator
    std::string numStr = source.substr(numberStart, current - numberStart);
    
    // Don't consume operators or other non-number characters
    if (peek() == '+' || peek() == '-' || peek() == '*' || peek() == '/' || 
        peek() == '(' || peek() == ')' || peek() == ';' || peek() == ' ' ||
        peek() == '\n' || peek() == '\t' || peek() == '\r' || isAtEnd())
    {
        return Token(
            (numStr.find('.') == std::string::npos) ? TokenType::INTEGER : TokenType::DOUBLE,
            numStr,
            std::stod(numStr),
            line,
            startColumn);
    }

    // If we get here, we have invalid characters after the number
    while (!isAtEnd() && !isspace(peek()) && peek() != ';' && 
           peek() != '+' && peek() != '-' && peek() != '*' && peek() != '/')
    {
        advance();
        column++;
    }
    
    return Token(TokenType::INVALID,
                source.substr(numberStart, current - numberStart),
                line,
                startColumn,
                "Invalid number format");
}

Token Lexer::identifier()
{
    int startColumn = column;
    std::string text;

    while (isAlphaNumeric(peek()))
    {
        text += peek();
        advance();
        column++;
    }

    // Check for invalid identifier patterns
    if (isDigit(text[0]))
    {
        return Token(TokenType::INVALID, text, line, startColumn, "");
    }

    // Check for other invalid patterns if needed
    // For example, check for invalid characters or reserved words

    auto it = keywords.find(text);
    if (it != keywords.end())
    {
        return Token(it->second, text, line, startColumn, "");
    }

    return Token(TokenType::IDENTIFIER, text, line, startColumn, "");
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
    int startColumn = column;

    if (isAtEnd())
        return Token(TokenType::EOF_TOKEN, std::string(""), line, startColumn, "");

    char c = advance();
    column++;

    // Handle special cases 'p' and 'r' first
    if (c == 'p' && peek() == '(') {
        return Token(TokenType::PRINT, std::string("p"), line, startColumn, "");
    }
    if (c == 'r' && peek() == '(') {
        return Token(TokenType::READ, std::string("r"), line, startColumn, "");
    }

    // Handle numbers
    if (isDigit(c)) {
        current--; // Move back to process the full number
        column--;
        return number();
    }

    // Handle identifiers and keywords
    if (isAlpha(c) || c == '_') {
        current--; // Move back to process the full identifier
        column--;
        return identifier();
    }

    // Handle operators and other single/double character tokens
    switch (c) {
        case '(': return Token(TokenType::LPAREN, "(", line, startColumn, "");
        case ')': return Token(TokenType::RPAREN, ")", line, startColumn, "");
        case '{': return Token(TokenType::LBRACE, "{", line, startColumn, "");
        case '}': return Token(TokenType::RBRACE, "}", line, startColumn, "");
        case ';': return Token(TokenType::SEMICOLON, ";", line, startColumn, "");
        case '+': return Token(TokenType::PLUS, "+", line, startColumn, "");
        case '-': return Token(TokenType::MINUS, "-", line, startColumn, "");
        case '*': 
            if (match('*')) {
                column++;
                return Token(TokenType::POWER, "**", line, startColumn, "");
            }
            return Token(TokenType::MULTIPLY, "*", line, startColumn, "");
        case '/': return Token(TokenType::DIVIDE, "/", line, startColumn, "");
        case '=':
            if (match('=')) {
                column++;
                return Token(TokenType::EQUAL_EQUAL, "==", line, startColumn, "");
            }
            return Token(TokenType::ASSIGN, "=", line, startColumn, "");
        case '<':
            if (match('=')) {
                column++;
                return Token(TokenType::LESS_EQUAL, "<=", line, startColumn, "");
            }
            return Token(TokenType::LESS, "<", line, startColumn, "");
        case '>':
            if (match('=')) {
                column++;
                return Token(TokenType::GREATER_EQUAL, ">=", line, startColumn, "");
            }
            return Token(TokenType::GREATER, ">", line, startColumn, "");
        case '!':
            if (match('=')) {
                column++;
                return Token(TokenType::NOT_EQUAL, "!=", line, startColumn, "");
            }
            return Token(TokenType::NOT, "!", line, startColumn, "");
        case '"': return string();
        case '&':
            if (match('&')) {
                column++;
                return Token(TokenType::AND, "&&", line, startColumn, "");
            }
            return Token(TokenType::INVALID, "&", line, startColumn, "Invalid operator: single '&' is not allowed");
        case '|':
            if (match('|')) {
                column++;
                return Token(TokenType::OR, "||", line, startColumn, "");
            }
            return Token(TokenType::INVALID, "|", line, startColumn, "Invalid operator: single '|' is not allowed");
    }

    // If we get here, we encountered an invalid character
    std::string invalidChar(1, c);
    return Token(TokenType::INVALID, 
                invalidChar, 
                line, 
                startColumn,
                "Invalid character in input");
}


void Lexer::skipWhitespace()
{
    while (true)
    {
        char c = peek();
        switch (c)
        {
        case ' ':
            current++;
            column++;
            start = current;
            break;
        case '\r':
            current++;
            start = current;
            break;
        case '\t':
            current++;
            column += 4;
            start = current;
            break;
        case '\n':
            line++;
            column = 1;
            current++;
            start = current;
            break;
        default:
            return;
        }
    }
}

Token Lexer::makeToken(TokenType type) const
{
    std::string text = source.substr(start, current - start);
    return Token(type, text, line, column - text.length(), "");
}

Token Lexer::makeToken(TokenType type, double value) const
{
    std::string text = source.substr(start, current - start);
    return Token(type, text, value, line, column - text.length());
}

Token Lexer::string()
{
    int startColumn = column - 1;
    advance(); // Skip the opening quote
    column++;

    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
        {
            return Token(TokenType::INVALID,
                         source.substr(start, current - (start)),
                         line, startColumn, "");
        }
        advance();
        column++;
    }

    if (isAtEnd() || peek() != '"')
    {
        return Token(TokenType::INVALID,
                     source.substr(start + 1, current - (start)),
                     line, startColumn, "");
    }

    std::string value = source.substr(start + 1, current - (start + 1));
    advance(); // Skip the closing quote
    column++;

    return Token(TokenType::STRING, value, line, startColumn, "");
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

void printTokens(const vector<Token> &tokens)
{
    // Print header
    cout << "\nTokenization Results:\n";
    cout << setw(10) << "Line" << setw(12) << "Column" << setw(25) << "Type" << setw(35) << "Value\n";
    cout << string(82, '-') << "\n";

    // Print each token, including INVALID tokens
    for (const auto &token : tokens)
    {
        cout << setw(10) << token.line
             << setw(12) << token.column
             << setw(25) << tokenTypeToString(token.type);

        // Handle value based on token type
        if (token.type == TokenType::INTEGER || token.type == TokenType::DOUBLE)
        {
            cout << setw(35) << token.numValue;
        }
        else if (token.type == TokenType::STRING)
        {
            cout << setw(35) << "\"" + token.lexeme + "\"";
        }
        else
        {
            cout << setw(35) << token.lexeme;
        }
        cout << "\n";
    }
    cout << "\n";
}

// Helper function to find start of current line
size_t Lexer::getLineStart() const
{
    size_t pos = start;
    while (pos > 0)
    {
        pos--;
        if (source[pos] == '\n')
        {
            return pos + 1;
        }
    }
    return 0;
}