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
        if (value.type == TokenType::BOOLEAN)
        {
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

class UnaryExpr : public Expression
{
public:
    Token op;
    ExprPtr right;

    UnaryExpr(Token op, ExprPtr right)
        : op(op), right(right) {}

    std::string toString() const override
    {
        return "(" + op.lexeme + right->toString() + ")";
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
        return "AssignmentStmt\n"
               "|-- Variable: " +
               name.lexeme + "\n"
                             "|-- Value: " +
               value->toString() + "\n";
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
        return "InputStmt\n"
               "|-- Variable: " +
               name.lexeme + "\n"
                             "|-- Prompt: \"" +
               prompt.lexeme + "\"\n";
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
        std::string result = "TypeDeclarationStmt\n"
                             "|-- Type: " +
                             type.lexeme + "\n"
                                           "|-- Name: " +
                             name.lexeme + "\n";

        if (inputStmt)
        {
            auto input = dynamic_pointer_cast<InputStmt>(inputStmt);
            result += "|-- Input:\n"
                      "    |-- Prompt: \"" +
                      input->prompt.lexeme + "\"\n";
        }
        else if (initializer)
        {
            result += "|-- Initializer: " + initializer->toString() + "\n";
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
        return "PrintStmt\n"
               "|-- Expression: " +
               expression->toString() + "\n";
    }
};

class BlockStmt : public Statement
{
public:
    vector<StmtPtr> statements;

    BlockStmt(vector<StmtPtr> statements) : statements(statements) {}

    std::string toString() const override
    {
        std::string result = "BlockStmt\n";
        for (const auto &stmt : statements)
        {
            // Indent each statement in the block
            std::string stmtStr = stmt->toString();
            // Add 4 spaces to each line of the statement
            size_t pos = 0;
            while ((pos = stmtStr.find('\n', pos)) != std::string::npos)
            {
                stmtStr.insert(pos + 1, "    ");
                pos += 5;
            }
            result += "    " + stmtStr;
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
        std::string result = "IfStmt\n"
                             "|-- Condition: " +
                             condition->toString() + "\n"
                                                     "|-- Then Branch:\n";

        // Add then branch with indentation
        std::string thenStr = thenBranch->toString();
        size_t pos = 0;
        while ((pos = thenStr.find('\n', pos)) != std::string::npos)
        {
            thenStr.insert(pos + 1, "    ");
            pos += 5;
        }
        result += "    " + thenStr;

        // Add else branch if it exists
        if (elseBranch)
        {
            result += "|-- Else Branch:\n";
            std::string elseStr = elseBranch->toString();
            pos = 0;
            while ((pos = elseStr.find('\n', pos)) != std::string::npos)
            {
                elseStr.insert(pos + 1, "    ");
                pos += 5;
            }
            result += "    " + elseStr;
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
        std::string result = "WhileStmt\n"
                             "|-- Condition: " +
                             condition->toString() + "\n"
                                                     "|-- Body:\n";

        // Add body with indentation
        std::string bodyStr = body->toString();
        size_t pos = 0;
        while ((pos = bodyStr.find('\n', pos)) != std::string::npos)
        {
            bodyStr.insert(pos + 1, "    ");
            pos += 5;
        }
        result += "    " + bodyStr;
        return result;
    }
};