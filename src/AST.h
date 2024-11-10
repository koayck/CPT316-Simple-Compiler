#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Token.h"

// Forward declarations
class Expression;
class Statement;

// shared pointers to Expression and Statement objects
using ExprPtr = shared_ptr<Expression>;
using StmtPtr = shared_ptr<Statement>;

// Base classes for AST nodes
class Expression
{
public:
    virtual ~Expression() = default;

    virtual std::string toString() const = 0;
};

class Statement
{
public:
    virtual ~Statement() = default;

    virtual std::string toString() const = 0;
};

// Expression nodes
class BinaryExpr : public Expression
{
public:
    ExprPtr left;
    Token op;
    ExprPtr right;

    BinaryExpr(ExprPtr left, Token op, ExprPtr right)
        : left(left), op(op), right(right) {}

    std::string toString() const override
    {
        return "(" + left->toString() + " " + op.lexeme + " " + right->toString() + ")";
    }
};

class LiteralExpr : public Expression
{
public:
    Token value;

    explicit LiteralExpr(Token value) : value(value) {}

    std::string toString() const override
    {
        return value.lexeme;
    }
};

class VariableExpr : public Expression
{
public:
    Token name;

    explicit VariableExpr(Token name) : name(name) {}

    std::string toString() const override
    {
        return name.lexeme;
    }
};

// Statement nodes
class AssignmentStmt : public Statement
{
public:
    Token name;
    ExprPtr value;

    AssignmentStmt(Token name, ExprPtr value)
        : name(name), value(value) {}

    std::string toString() const override
    {
        return name.lexeme + " = " + value->toString() + ";";
    }
};

class PrintStmt : public Statement
{
public:
    Token stringToPrint;

    explicit PrintStmt(Token stringToPrint) : stringToPrint(stringToPrint) {}

    std::string toString() const override
    {
        return "print(" + stringToPrint.lexeme + ");";
    }
};

class InputStmt : public Statement
{
public:
    Token name;
    Token prompt;

    InputStmt(Token name, Token prompt)
        : name(name), prompt(prompt) {}

    std::string toString() const override
    {
        return name.lexeme + " = read(" + prompt.lexeme + ");";
    }
};

class IfStmt : public Statement
{
public:
    ExprPtr condition;
    vector<StmtPtr> thenBranch;
    vector<StmtPtr> elseBranch;

    IfStmt(ExprPtr condition, vector<StmtPtr> thenBranch, vector<StmtPtr> elseBranch)
        : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

    std::string toString() const override
    {
        std::string result = "if " + condition->toString() + " {\n";
        for (const auto &stmt : thenBranch)
        {
            result += "  " + stmt->toString() + "\n";
        }
        result += "}";
        if (!elseBranch.empty())
        {
            result += " else {\n";
            for (const auto &stmt : elseBranch)
            {
                result += "  " + stmt->toString() + "\n";
            }
            result += "}";
        }
        return result;
    }
};

class WhileStmt : public Statement
{
public:
    ExprPtr condition;
    vector<StmtPtr> body;

    WhileStmt(ExprPtr condition, vector<StmtPtr> body)
        : condition(condition), body(body) {}

    std::string toString() const override
    {
        std::string result = "while " + condition->toString() + " {\n";
        for (const auto &stmt : body)
        {
            result += "  " + stmt->toString() + "\n";
        }
        result += "}";
        return result;
    }
};