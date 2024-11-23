/**
 * @file AST.h
 * @brief Abstract Syntax Tree node definitions for MiniLang
 * 
 * This file defines the class hierarchy for the Abstract Syntax Tree (AST).
 * The AST represents the syntactic structure of the program in a tree format.
 * 
 * Class hierarchy:
 * - Expression (abstract base class for expressions)
 *   - BinaryExpr (arithmetic and comparison operations)
 *   - LiteralExpr (numbers and strings)
 *   - VariableExpr (variable references)
 * 
 * - Statement (abstract base class for statements)
 *   - AssignmentStmt (variable assignments)
 *   - TypeDeclarationStmt (variable declarations)
 *   - PrintStmt (print statements)
 *   - InputStmt (read statements)
 *   - IfStmt (conditional statements)
 *   - WhileStmt (loops)
 */

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
        if (value.type == TokenType::BOOLEAN) {
            return value.numValue != 0 ? "true" : "false";
        }
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

class InputStmt : public Statement
{
public:
    Token name;
    Token prompt;

    InputStmt(Token name, Token prompt)
        : name(name), prompt(prompt) {}

    std::string toString() const override
    {
        return name.lexeme + " = read(\"" + prompt.lexeme + "\");";
    }
};

class TypeDeclarationStmt : public Statement
{
public:
    Token type;
    Token name;
    ExprPtr initializer;
    StmtPtr inputStmt;

    TypeDeclarationStmt(Token type, Token name, ExprPtr initializer, StmtPtr inputStmt = nullptr)
        : type(type), name(name), initializer(initializer), inputStmt(inputStmt) {}

    std::string toString() const override
    {
        if (inputStmt) {
            auto input = dynamic_pointer_cast<InputStmt>(inputStmt);
            return type.lexeme + " " + name.lexeme + " = r(\"" + input->prompt.lexeme + "\");";
        }
        if (initializer)
        {
            return type.lexeme + " " + name.lexeme + " = " + initializer->toString() + ";";
        }
        return type.lexeme + " " + name.lexeme + ";";
    }
};

class PrintStmt : public Statement
{
public:
    ExprPtr expression;

    explicit PrintStmt(ExprPtr expression) : expression(expression) {}

    std::string toString() const override
    {
        return "print " + expression->toString() + ";";
    }
};

class IfStmt : public Statement
{
public:
    ExprPtr condition;
    StmtPtr thenBranch;
    StmtPtr elseBranch;

    IfStmt(ExprPtr condition, StmtPtr thenBranch, StmtPtr elseBranch)
        : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

    std::string toString() const override
    {
        std::string result = "if (" + condition->toString() + ") ";
        result += thenBranch->toString();
        if (elseBranch)
        {
            result += " else " + elseBranch->toString();
        }
        return result;
    }
};

class WhileStmt : public Statement
{
public:
    ExprPtr condition;
    StmtPtr body;

    WhileStmt(ExprPtr condition, StmtPtr body)
        : condition(condition), body(body) {}

    std::string toString() const override
    {
        return "while (" + condition->toString() + ") " + body->toString();
    }
};