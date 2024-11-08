
// Generated from c:/Users/kck03/Desktop/CPT316-Simple-Compiler/MiniLang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "MiniLangParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MiniLangParser.
 */
class  MiniLangVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MiniLangParser.
   */
    virtual std::any visitProgram(MiniLangParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(MiniLangParser::StatementContext *context) = 0;

    virtual std::any visitAssignment(MiniLangParser::AssignmentContext *context) = 0;

    virtual std::any visitOutput(MiniLangParser::OutputContext *context) = 0;

    virtual std::any visitInput(MiniLangParser::InputContext *context) = 0;

    virtual std::any visitIfStatement(MiniLangParser::IfStatementContext *context) = 0;

    virtual std::any visitWhileLoop(MiniLangParser::WhileLoopContext *context) = 0;

    virtual std::any visitDoubleExpr(MiniLangParser::DoubleExprContext *context) = 0;

    virtual std::any visitMulDivExpr(MiniLangParser::MulDivExprContext *context) = 0;

    virtual std::any visitVarExpr(MiniLangParser::VarExprContext *context) = 0;

    virtual std::any visitIntExpr(MiniLangParser::IntExprContext *context) = 0;

    virtual std::any visitParenExpr(MiniLangParser::ParenExprContext *context) = 0;

    virtual std::any visitExpExpr(MiniLangParser::ExpExprContext *context) = 0;

    virtual std::any visitAddSubExpr(MiniLangParser::AddSubExprContext *context) = 0;

    virtual std::any visitCondition(MiniLangParser::ConditionContext *context) = 0;

    virtual std::any visitRelop(MiniLangParser::RelopContext *context) = 0;


};

