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
 *   - UnaryExpr (unary operations)
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

// Abstract base classes for AST nodes
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

// Helper function for indentation
static string indent(const string& str, const string& prefix) {
    string result;
    istringstream stream(str);
    string line;
    while (getline(stream, line)) {
        if (!line.empty()) {
            result += prefix + line + "\n";
        }
    }
    return result;
}

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
        std::string result = "BinaryExpression (" + op.lexeme + ")\n";
        result += "|-- LeftOperand\n";
        result += "|   " + left->toString() + "\n";
        result += "|-- RightOperand\n";
        result += "    " + right->toString();
        return result;
    }
};

class LiteralExpr : public Expression
{
public:
    Token value;

    explicit LiteralExpr(Token value) : value(value) {}

    std::string toString() const override
    {
        if (value.type == TokenType::BOOLEAN)
        {
            return "Literal: " + std::string(value.numValue != 0 ? "true" : "false");
        }
        return "Literal: " + value.lexeme;
    }
};

class VariableExpr : public Expression
{
public:
    Token name;

    explicit VariableExpr(Token name) : name(name) {}

    std::string toString() const override
    {
        return "Variable: " + name.lexeme;
    }
};

class UnaryExpr : public Expression
{
public:
    Token op;
    ExprPtr right;

    UnaryExpr(Token op, ExprPtr right)
        : op(op), right(right) {}

    std::string toString() const override
    {
        return "UnaryExpression (" + op.lexeme + ")\n"
               "|-- Operand\n"
               "    " + right->toString();
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
        std::string result = "AssignmentStatement\n";
        result += "|-- Identifier: " + name.lexeme + "\n";
        result += "|-- Expression\n";
        result += "    " + indent(value->toString(), "    ");
        return result;
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
        return "ReadStatement\n"
               "|-- Identifier\n"
               "|   " + name.lexeme + "\n"
               "|-- PromptString\n"
               "    \"" + prompt.lexeme + "\"";
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
        std::string result = "VariableDeclaration\n";
        result += "|-- Type: " + type.lexeme + "\n";
        result += "|-- Name: " + name.lexeme;
        
        if (inputStmt) {
            auto input = dynamic_pointer_cast<InputStmt>(inputStmt);
            result += "\n|-- Input\n";
            result += "    |-- Prompt: \"" + input->prompt.lexeme + "\"";
        }
        else if (initializer) {
            result += "\n|-- Value\n";
            result += "    " + indent(initializer->toString(), "    ");
        }
        return result;
    }
};

class PrintStmt : public Statement
{
public:
    ExprPtr expression;

    explicit PrintStmt(ExprPtr expression) : expression(expression) {}

    std::string toString() const override
    {
        return "PrintStatement\n"
               "|-- Expression\n"
               "    " + indent(expression->toString(), "    ");
    }
};

class BlockStmt : public Statement
{
public:
    vector<StmtPtr> statements;

    BlockStmt(vector<StmtPtr> statements) : statements(statements) {}

    std::string toString() const override
    {
        std::string result = "Block";
        for (size_t i = 0; i < statements.size(); i++) {
            bool isLast = (i == statements.size() - 1);
            result += "\n|-- Statement[" + std::to_string(i+1) + "]\n";
            result += (isLast ? "    " : "|   ") + 
                     indent(statements[i]->toString(), isLast ? "    " : "|   ");
        }
        return result;
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
        std::string result = "IfStatement\n";
        result += "|-- Condition\n";
        result += "|   " + indent(condition->toString(), "|   ");
        result += "|-- Then\n";
        result += "|   " + indent(thenBranch->toString(), "|   ");
        
        if (elseBranch) {
            result += "|-- Else\n";
            result += "    " + indent(elseBranch->toString(), "    ");
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
        std::string result = "WhileLoop\n";
        result += "|-- Condition\n";
        result += "|   " + indent(condition->toString(), "|   ");
        result += "|-- Body\n";
        result += "    " + indent(body->toString(), "    ");
        return result;
    }
};