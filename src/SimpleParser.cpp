#include "SimpleParser.h"

SimpleParser::SimpleParser(const std::vector<Token> &tokens) : tokens(tokens), pos(0) {}

std::shared_ptr<ASTNode> SimpleParser::parse() {
    return program();
}

Token SimpleParser::peek() const {
    if (pos < tokens.size()) {
        return tokens[pos];
    }
    return {TokenType::UNKNOWN, ""};
}

Token SimpleParser::get() {
    if (pos < tokens.size()) {
        return tokens[pos++];
    }
    return {TokenType::UNKNOWN, ""};
}

std::shared_ptr<ASTNode> SimpleParser::program() {
    auto node = std::make_shared<ASTNode>("Program", "");
    while (pos < tokens.size()) {
        node->children.push_back(statement());
    }
    return node;
}

std::shared_ptr<ASTNode> SimpleParser::statement() {
    auto token = peek();
    if (token.type == TokenType::IDENTIFIER) {
        return expression();
    } else if (token.type == TokenType::COMMENT) {
        get(); // Consume the comment token
        return std::make_shared<ASTNode>("Comment", token.value);
    } else {
        // Handle other types of statements (e.g., assignment, output, input)
        return std::make_shared<ASTNode>("Unknown", token.value);
    }
}

std::shared_ptr<ASTNode> SimpleParser::expression() {
    auto node = term();
    while (true) {
        auto token = peek();
        if (token.type == TokenType::ADD || token.type == TokenType::SUB) {
            get(); // Consume the operator
            auto newNode = std::make_shared<ASTNode>("BinaryOp", token.value);
            newNode->children.push_back(node);
            newNode->children.push_back(term());
            node = newNode;
        } else {
            break;
        }
    }
    return node;
}

std::shared_ptr<ASTNode> SimpleParser::term() {
    auto node = factor();
    while (true) {
        auto token = peek();
        if (token.type == TokenType::MUL || token.type == TokenType::DIV) {
            get(); // Consume the operator
            auto newNode = std::make_shared<ASTNode>("BinaryOp", token.value);
            newNode->children.push_back(node);
            newNode->children.push_back(factor());
            node = newNode;
        } else {
            break;
        }
    }
    return node;
}

std::shared_ptr<ASTNode> SimpleParser::factor() {
    auto token = get();
    if (token.type == TokenType::INT || token.type == TokenType::DOUBLE) {
        return std::make_shared<ASTNode>("Number", token.value);
    } else if (token.type == TokenType::IDENTIFIER) {
        return std::make_shared<ASTNode>("Identifier", token.value);
    } else if (token.type == TokenType::LPAREN) {
        auto node = expression();
        get(); // Consume the closing parenthesis
        return node;
    } else {
        return std::make_shared<ASTNode>("Unknown", token.value);
    }
}