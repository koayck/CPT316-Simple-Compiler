#include "Lexer.h"
#include <unordered_map>
#include <string>

using namespace std;

static const unordered_map<string, TokenType> keywords = {
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE}};

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

    tokens.push_back(Token(TokenType::EOF_TOKEN, ""));
    return tokens;
}

Token Lexer::number()
{
    while (isDigit(peek()))
        advance(); // Consume digits

    // Check for a fractional part
    if (peek() == '.')
    {
        advance(); // Consume the '.'
        while (isDigit(peek()))
            advance(); // Consume digits after the '.'

        // Convert the substring to a double
        double value = stod(source.substr(start, current - start));
        return makeToken(TokenType::DOUBLE, value); // Return as DOUBLE token
    }

    // Convert the substring to an integer
    int intValue = stoi(source.substr(start, current - start));
    return makeToken(TokenType::INTEGER, intValue); // Return as INTEGER token
}

Token Lexer::identifier()
{
    while (isAlphaNumeric(peek()))
        advance(); // Consume alphanumeric characters

    std::string text = source.substr(start, current - start);

    // if the identifier is a keyword, return the corresponding token
    if (keywords.find(text) != keywords.end())
    {
        return makeToken(static_cast<TokenType>(keywords.at(text)));
    }

    // If it's not a keyword, return an IDENTIFIER token
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

    // retrieve character at current index before advancing the position
    char c = advance();

    if (isDigit(c))
        return number();
    if (isAlpha(c))
        return identifier();

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
        return makeToken(TokenType::PRINT);
    case 'r':
        return makeToken(TokenType::READ);
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
    return Token(type, text);
}

Token Lexer::makeToken(TokenType type, double value) const
{
    std::string text = source.substr(start, current - start);
    return Token(type, text, value);
}

Token Lexer::string()
{
    // Skip the opening quote
    advance();

    start = current;
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

    // Get the string content
    std::string value = source.substr(start, current - start);

    // Skip the closing quote
    advance();

    return Token(TokenType::STRING, value);
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
    default:
        return "UNKNOWN"; // Fallback for any unrecognized type
    }
}