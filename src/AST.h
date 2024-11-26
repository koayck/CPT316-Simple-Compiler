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
        // Helper function to indent each line of a string
        auto indentString = [](const std::string& str, const std::string& indent) {
            std::string result;
            size_t pos = 0, lastPos = 0;
            while ((pos = str.find('\n', lastPos)) != std::string::npos) {
                result += indent + str.substr(lastPos, pos - lastPos + 1);
                lastPos = pos + 1;
            }
            if (lastPos < str.length()) {
                result += indent + str.substr(lastPos);
            }
            return result;
        };

        std::string leftStr = left->toString();
        std::string rightStr = right->toString();

        return "BinaryExpression (" + op.lexeme + ")\n"
               "|-- LeftOperand\n"
               "|   " + indentString(leftStr, "|   ").substr(4) + "\n"
               "|-- RightOperand\n"
               "    " + indentString(rightStr, "    ").substr(4);
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
        // Helper function to indent each line of a string
        auto indentString = [](const std::string& str, const std::string& indent) {
            std::string result;
            size_t pos = 0, lastPos = 0;
            while ((pos = str.find('\n', lastPos)) != std::string::npos) {
                result += indent + str.substr(lastPos, pos - lastPos + 1);
                lastPos = pos + 1;
            }
            if (lastPos < str.length()) {
                result += indent + str.substr(lastPos);
            }
            return result;
        };

        std::string exprStr = value->toString();
        
        return "AssignmentStatement\n"
               "|-- Identifier\n"
               "|   " + name.lexeme + "\n"
               "|-- Expression\n"
               "    " + indentString(exprStr, "    ").substr(4);
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
        std::string result = "VariableDeclaration\n"
                            "|-- DataType\n"
                            "|   " + type.lexeme + "\n"
                            "|-- Identifier\n";
        
        if (inputStmt || initializer)
        {
            result += "|   " + name.lexeme;
            if (inputStmt)
            {
                auto input = dynamic_pointer_cast<InputStmt>(inputStmt);
                result += "\n|-- Initializer (Read)\n"
                         "    PromptString: \"" + input->prompt.lexeme + "\"";
            }
            else if (initializer)
            {
                result += "\n|-- InitializerExpression\n"
                         "    " + initializer->toString();
            }
        }
        else
        {
            result += "    " + name.lexeme;
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
               "    " + expression->toString();
    }
};

class BlockStmt : public Statement
{
public:
    vector<StmtPtr> statements;

    BlockStmt(vector<StmtPtr> statements) : statements(statements) {}

    std::string toString() const override
    {
        std::string result = "CompoundStatement\n";
        for (size_t i = 0; i < statements.size(); i++)
        {
            std::string stmtStr = statements[i]->toString();
            if (i < statements.size() - 1) {
                result += "|-- Statement[" + std::to_string(i+1) + "]\n";
                size_t pos = 0;
                while ((pos = stmtStr.find('\n', pos)) != std::string::npos)
                {
                    stmtStr.insert(pos + 1, "|   ");
                    pos += 5;
                }
                result += "|   " + stmtStr + "\n";
            } else {
                result += "|-- Statement[" + std::to_string(i+1) + "]\n";
                size_t pos = 0;
                while ((pos = stmtStr.find('\n', pos)) != std::string::npos)
                {
                    stmtStr.insert(pos + 1, "    ");
                    pos += 5;
                }
                result += "    " + stmtStr + "\n";
            }
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
        std::string result = "ConditionalStatement\n"
                            "|-- Condition\n"
                            "|   " + condition->toString() + "\n"
                            "|-- ThenBranch\n";
        
        if (elseBranch)
        {
            result += "|   " + thenBranch->toString() + "\n"
                     "|-- ElseBranch\n"
                     "    " + elseBranch->toString();
        }
        else
        {
            result += "    " + thenBranch->toString();
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
        return "WhileStatement\n"
               "|-- Condition\n"
               "|   " + condition->toString() + "\n"
               "|-- Body\n"
               "    " + body->toString();
    }
};