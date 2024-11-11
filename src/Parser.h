#pragma once
#include "Token.h"
#include "AST.h"
#include <vector>
#include <stdexcept>
#include <string>

class Parser
{
public:
    explicit Parser(const vector<Token> &tokens)
        : tokens(tokens), current(0) {}

    vector<StmtPtr> parse();

private:
    vector<Token> tokens;
    size_t current;

    bool isAtEnd() const;
    Token peek() const;
    Token peekNext(int lookahead = 1) const;
    Token previous() const;
    Token advance();
    bool check(TokenType type) const;
    bool match(TokenType type);

    StmtPtr statement();
    StmtPtr typeDeclarationStatement();
    StmtPtr assignmentStatement();
    StmtPtr printStatement();
    StmtPtr inputStatement();
    StmtPtr ifStatement();
    StmtPtr whileStatement();

    ExprPtr comparison();
    ExprPtr expression();
    ExprPtr term();
    ExprPtr factor();
    ExprPtr power();
    ExprPtr primary();

    void consume(TokenType type, const std::string &message);
};