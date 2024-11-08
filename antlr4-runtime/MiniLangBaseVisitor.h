
// Generated from c:/Users/kck03/Desktop/CPT316-Simple-Compiler/MiniLang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "MiniLangVisitor.h"


/**
 * This class provides an empty implementation of MiniLangVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MiniLangBaseVisitor : public MiniLangVisitor {
public:

  virtual std::any visitProgram(MiniLangParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(MiniLangParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(MiniLangParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOutput(MiniLangParser::OutputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInput(MiniLangParser::InputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(MiniLangParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileLoop(MiniLangParser::WhileLoopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoubleExpr(MiniLangParser::DoubleExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDivExpr(MiniLangParser::MulDivExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarExpr(MiniLangParser::VarExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntExpr(MiniLangParser::IntExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(MiniLangParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpExpr(MiniLangParser::ExpExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSubExpr(MiniLangParser::AddSubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(MiniLangParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelop(MiniLangParser::RelopContext *ctx) override {
    return visitChildren(ctx);
  }


};

