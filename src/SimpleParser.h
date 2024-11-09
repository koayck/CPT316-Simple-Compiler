#pragma once

#include <string>
#include <vector>
#include <memory>
#include "SimpleLexer.h"

class ASTNode {
public:
    std::string type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(const std::string &type, const std::string &value) : type(type), value(value) {}
};

class SimpleParser {
public:
    explicit SimpleParser(const std::vector<Token> &tokens);
    std::shared_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens;
    size_t pos;

    Token peek() const;
    Token get();
    std::shared_ptr<ASTNode> program();
    std::shared_ptr<ASTNode> statement();
    std::shared_ptr<ASTNode> expression();
    std::shared_ptr<ASTNode> term();
    std::shared_ptr<ASTNode> factor();
};