#include "SimpleLexer.h"
#include <cctype>
#include <string>

using namespace std;

SimpleLexer::SimpleLexer(const std::string &input) : input(input), pos(0) {}

/**
 * @brief Tokenizes the input string into a vector of tokens.
 * 
 * This function processes the input string character by character, identifying
 * and categorizing different types of tokens such as identifiers, numbers, strings,
 * comments, and various operators. It skips whitespace and handles special cases
 * like the exponentiation operator (**).
 * 
 * @return vector<Token> A vector containing the tokens identified in the input string.
 */
vector<Token> SimpleLexer::tokenize() {
    vector<Token> tokens;
    while (pos < input.size()) {
        skipWhitespace();
        if (pos >= input.size()) break;

        char current = peek();
        if (isalpha(current) || current == '_') {
            tokens.push_back(identifier());
        } else if (isdigit(current)) {
            tokens.push_back(number());
        } else if (current == '"') {
            tokens.push_back(string());
        } else if (current == '#') {
            tokens.push_back(comment());
        } else {
            switch (current) {
                case '+': tokens.push_back({TokenType::ADD, std::string(1, get())}); break;
                case '-': tokens.push_back({TokenType::SUB, std::string(1, get())}); break;
                case '*': 
                    get();
                    if (peek() == '*') {
                        get();
                        tokens.push_back({TokenType::EXP, "**"});
                    } else {
                        tokens.push_back({TokenType::MUL, "*"});
                    }
                    break;
                case '/': tokens.push_back({TokenType::DIV, std::string(1, get())}); break;
                case ';': tokens.push_back({TokenType::SEPARATOR, std::string(1, get())}); break;
                case '(': tokens.push_back({TokenType::LPAREN, std::string(1, get())}); break;
                case ')': tokens.push_back({TokenType::RPAREN, std::string(1, get())}); break;
                case '{': tokens.push_back({TokenType::LBRACE, std::string(1, get())}); break;
                case '}': tokens.push_back({TokenType::RBRACE, std::string(1, get())}); break;
                default: tokens.push_back({TokenType::UNKNOWN, std::string(1, get())}); break;
            }
        }
    }
    return tokens;
}

char SimpleLexer::peek() const {
    return input[pos];
}

char SimpleLexer::get() {
    return input[pos++];
}

void SimpleLexer::skipWhitespace() {
    while (pos < input.size() && isspace(input[pos])) {
        pos++;
    }
}

Token SimpleLexer::identifier() {
    size_t start = pos;
    while (pos < input.size() && (isalnum(input[pos]) || input[pos] == '_')) {
        pos++;
    }
    return {TokenType::IDENTIFIER, input.substr(start, pos - start)};
}

Token SimpleLexer::number() {
    size_t start = pos;
    while (pos < input.size() && isdigit(input[pos])) {
        pos++;
    }
    if (pos < input.size() && input[pos] == '.') {
        pos++;
        while (pos < input.size() && isdigit(input[pos])) {
            pos++;
        }
        return {TokenType::DOUBLE, input.substr(start, pos - start)};
    }
    return {TokenType::INT, input.substr(start, pos - start)};
}

Token SimpleLexer::string() {
    size_t start = ++pos; // Skip the opening quote
    while (pos < input.size() && input[pos] != '"') {
        pos++;
    }
    pos++; // Skip the closing quote
    return {TokenType::STRING, input.substr(start, pos - start - 1)};
}

Token SimpleLexer::comment() {
    size_t start = pos;
    while (pos < input.size() && input[pos] != '\n') {
        pos++;
    }
    return {TokenType::COMMENT, input.substr(start, pos - start)};
}

string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::INT: return "INT";
        case TokenType::DOUBLE: return "DOUBLE";
        case TokenType::STRING: return "STRING";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::WS: return "WS";
        case TokenType::ADD: return "ADD";
        case TokenType::SUB: return "SUB";
        case TokenType::MUL: return "MUL";
        case TokenType::DIV: return "DIV";
        case TokenType::EXP: return "EXP";
        case TokenType::SEPARATOR: return "SEPARATOR";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::LBRACE: return "LBRACE";
        case TokenType::RBRACE: return "RBRACE";
        case TokenType::UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}