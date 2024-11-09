#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Token.h"

using namespace std;

// Forward declarations
class Expression;
class Statement;

// shared pointers to Expression and Statement objects
using ExprPtr = shared_ptr<Expression>;
using StmtPtr = shared_ptr<Statement>;

// Base classes for AST nodes
class Expression {
public:
    virtual ~Expression() = default;
};

class Statement {
public:
    virtual ~Statement() = default;
};

// Expression nodes
class BinaryExpr : public Expression {
public:
    ExprPtr left;
    Token op;
    ExprPtr right;
    
    BinaryExpr(ExprPtr left, Token op, ExprPtr right)
        : left(left), op(op), right(right) {}
};

class LiteralExpr : public Expression {
public:
    Token value;
    
    explicit LiteralExpr(Token value) : value(value) {}
};

class VariableExpr : public Expression {
public:
    Token name;
    
    explicit VariableExpr(Token name) : name(name) {}
};

// Statement nodes
class AssignmentStmt : public Statement {
public:
    Token name;
    ExprPtr value;
    
    AssignmentStmt(Token name, ExprPtr value)
        : name(name), value(value) {}
};

class PrintStmt : public Statement {
public:
    Token string;
    
    explicit PrintStmt(Token string) : string(string) {}
};

class InputStmt : public Statement {
public:
    Token name;
    Token prompt;
    
    InputStmt(Token name, Token prompt)
        : name(name), prompt(prompt) {}
};

class IfStmt : public Statement {
public:
    ExprPtr condition;
    vector<StmtPtr> thenBranch;
    vector<StmtPtr> elseBranch;
    
    IfStmt(ExprPtr condition, vector<StmtPtr> thenBranch, vector<StmtPtr> elseBranch)
        : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

class WhileStmt : public Statement {
public:
    ExprPtr condition;
    vector<StmtPtr> body;
    
    WhileStmt(ExprPtr condition, vector<StmtPtr> body)
        : condition(condition), body(body) {}
}; 