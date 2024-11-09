#pragma once
#include "Token.h"
#include "AST.h"
#include <vector>
#include <stdexcept>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens) 
        : tokens(tokens), current(0) {}
    
    std::vector<StmtPtr> parse();

private:
    std::vector<Token> tokens;
    size_t current;
    
    bool isAtEnd() const { return peek().type == TokenType::EOF_TOKEN; }
    Token peek() const { return tokens[current]; }
    Token previous() const { return tokens[current - 1]; }
    Token advance() { if (!isAtEnd()) current++; return previous(); }
    bool check(TokenType type) const { return !isAtEnd() && peek().type == type; }
    bool match(TokenType type);
    
    StmtPtr statement();
    StmtPtr assignmentStatement();
    StmtPtr printStatement();
    StmtPtr inputStatement();
    StmtPtr ifStatement();
    StmtPtr whileStatement();
    
    ExprPtr expression();
    ExprPtr term();
    ExprPtr factor();
    ExprPtr power();
    ExprPtr primary();
    
    void consume(TokenType type, const std::string& message);
}; 