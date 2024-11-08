
// Generated from c:/Users/kck03/Desktop/CPT316-Simple-Compiler/MiniLang.g4 by ANTLR 4.13.1


#include "MiniLangVisitor.h"

#include "MiniLangParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MiniLangParserStaticData final {
  MiniLangParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MiniLangParserStaticData(const MiniLangParserStaticData&) = delete;
  MiniLangParserStaticData(MiniLangParserStaticData&&) = delete;
  MiniLangParserStaticData& operator=(const MiniLangParserStaticData&) = delete;
  MiniLangParserStaticData& operator=(MiniLangParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag minilangParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
MiniLangParserStaticData *minilangParserStaticData = nullptr;

void minilangParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (minilangParserStaticData != nullptr) {
    return;
  }
#else
  assert(minilangParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MiniLangParserStaticData>(
    std::vector<std::string>{
      "program", "statement", "assignment", "output", "input", "ifStatement", 
      "whileLoop", "expression", "condition", "relop"
    },
    std::vector<std::string>{
      "", "'='", "'p'", "'r'", "'if'", "'else'", "'while'", "'!'", "'&&'", 
      "'||'", "'>'", "'<'", "'>='", "'<='", "'=='", "'!='", "", "", "", 
      "", "", "", "'+'", "'-'", "'*'", "'/'", "'**'", "';'", "'('", "')'", 
      "'{'", "'}'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "IDENTIFIER", 
      "INT", "DOUBLE", "STRING", "COMMENT", "WS", "ADD", "SUB", "MUL", "DIV", 
      "EXP", "SEPARATOR", "LPAREN", "RPAREN", "LBRACE", "RBRACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,31,133,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,1,0,4,0,22,8,0,11,0,12,0,23,1,0,1,0,1,1,1,1,1,1,
  	1,1,1,1,1,1,3,1,34,8,1,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,5,5,59,8,5,10,5,12,5,62,
  	9,5,1,5,1,5,1,5,1,5,5,5,68,8,5,10,5,12,5,71,9,5,1,5,3,5,74,8,5,1,6,1,
  	6,1,6,1,6,5,6,80,8,6,10,6,12,6,83,9,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,3,7,95,8,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,5,7,106,8,7,10,
  	7,12,7,109,9,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,118,8,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,5,8,126,8,8,10,8,12,8,129,9,8,1,9,1,9,1,9,0,2,14,16,10,0,2,
  	4,6,8,10,12,14,16,18,0,3,1,0,24,25,1,0,22,23,1,0,10,15,141,0,21,1,0,0,
  	0,2,33,1,0,0,0,4,35,1,0,0,0,6,40,1,0,0,0,8,46,1,0,0,0,10,54,1,0,0,0,12,
  	75,1,0,0,0,14,94,1,0,0,0,16,117,1,0,0,0,18,130,1,0,0,0,20,22,3,2,1,0,
  	21,20,1,0,0,0,22,23,1,0,0,0,23,21,1,0,0,0,23,24,1,0,0,0,24,25,1,0,0,0,
  	25,26,5,0,0,1,26,1,1,0,0,0,27,34,3,4,2,0,28,34,3,6,3,0,29,34,3,8,4,0,
  	30,34,3,10,5,0,31,34,3,12,6,0,32,34,5,20,0,0,33,27,1,0,0,0,33,28,1,0,
  	0,0,33,29,1,0,0,0,33,30,1,0,0,0,33,31,1,0,0,0,33,32,1,0,0,0,34,3,1,0,
  	0,0,35,36,5,16,0,0,36,37,5,1,0,0,37,38,3,14,7,0,38,39,5,27,0,0,39,5,1,
  	0,0,0,40,41,5,2,0,0,41,42,5,28,0,0,42,43,5,19,0,0,43,44,5,29,0,0,44,45,
  	5,27,0,0,45,7,1,0,0,0,46,47,5,16,0,0,47,48,5,1,0,0,48,49,5,3,0,0,49,50,
  	5,28,0,0,50,51,5,19,0,0,51,52,5,29,0,0,52,53,5,27,0,0,53,9,1,0,0,0,54,
  	55,5,4,0,0,55,56,3,16,8,0,56,60,5,30,0,0,57,59,3,2,1,0,58,57,1,0,0,0,
  	59,62,1,0,0,0,60,58,1,0,0,0,60,61,1,0,0,0,61,63,1,0,0,0,62,60,1,0,0,0,
  	63,73,5,31,0,0,64,65,5,5,0,0,65,69,5,30,0,0,66,68,3,2,1,0,67,66,1,0,0,
  	0,68,71,1,0,0,0,69,67,1,0,0,0,69,70,1,0,0,0,70,72,1,0,0,0,71,69,1,0,0,
  	0,72,74,5,31,0,0,73,64,1,0,0,0,73,74,1,0,0,0,74,11,1,0,0,0,75,76,5,6,
  	0,0,76,77,3,16,8,0,77,81,5,30,0,0,78,80,3,2,1,0,79,78,1,0,0,0,80,83,1,
  	0,0,0,81,79,1,0,0,0,81,82,1,0,0,0,82,84,1,0,0,0,83,81,1,0,0,0,84,85,5,
  	31,0,0,85,13,1,0,0,0,86,87,6,7,-1,0,87,88,5,28,0,0,88,89,3,14,7,0,89,
  	90,5,29,0,0,90,95,1,0,0,0,91,95,5,16,0,0,92,95,5,17,0,0,93,95,5,18,0,
  	0,94,86,1,0,0,0,94,91,1,0,0,0,94,92,1,0,0,0,94,93,1,0,0,0,95,107,1,0,
  	0,0,96,97,10,7,0,0,97,98,7,0,0,0,98,106,3,14,7,8,99,100,10,6,0,0,100,
  	101,7,1,0,0,101,106,3,14,7,7,102,103,10,5,0,0,103,104,5,26,0,0,104,106,
  	3,14,7,6,105,96,1,0,0,0,105,99,1,0,0,0,105,102,1,0,0,0,106,109,1,0,0,
  	0,107,105,1,0,0,0,107,108,1,0,0,0,108,15,1,0,0,0,109,107,1,0,0,0,110,
  	111,6,8,-1,0,111,112,3,14,7,0,112,113,3,18,9,0,113,114,3,14,7,0,114,118,
  	1,0,0,0,115,116,5,7,0,0,116,118,3,16,8,3,117,110,1,0,0,0,117,115,1,0,
  	0,0,118,127,1,0,0,0,119,120,10,2,0,0,120,121,5,8,0,0,121,126,3,16,8,3,
  	122,123,10,1,0,0,123,124,5,9,0,0,124,126,3,16,8,2,125,119,1,0,0,0,125,
  	122,1,0,0,0,126,129,1,0,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,17,1,
  	0,0,0,129,127,1,0,0,0,130,131,7,2,0,0,131,19,1,0,0,0,12,23,33,60,69,73,
  	81,94,105,107,117,125,127
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  minilangParserStaticData = staticData.release();
}

}

MiniLangParser::MiniLangParser(TokenStream *input) : MiniLangParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MiniLangParser::MiniLangParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MiniLangParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *minilangParserStaticData->atn, minilangParserStaticData->decisionToDFA, minilangParserStaticData->sharedContextCache, options);
}

MiniLangParser::~MiniLangParser() {
  delete _interpreter;
}

const atn::ATN& MiniLangParser::getATN() const {
  return *minilangParserStaticData->atn;
}

std::string MiniLangParser::getGrammarFileName() const {
  return "MiniLang.g4";
}

const std::vector<std::string>& MiniLangParser::getRuleNames() const {
  return minilangParserStaticData->ruleNames;
}

const dfa::Vocabulary& MiniLangParser::getVocabulary() const {
  return minilangParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MiniLangParser::getSerializedATN() const {
  return minilangParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

MiniLangParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniLangParser::ProgramContext::EOF() {
  return getToken(MiniLangParser::EOF, 0);
}

std::vector<MiniLangParser::StatementContext *> MiniLangParser::ProgramContext::statement() {
  return getRuleContexts<MiniLangParser::StatementContext>();
}

MiniLangParser::StatementContext* MiniLangParser::ProgramContext::statement(size_t i) {
  return getRuleContext<MiniLangParser::StatementContext>(i);
}


size_t MiniLangParser::ProgramContext::getRuleIndex() const {
  return MiniLangParser::RuleProgram;
}


std::any MiniLangParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::ProgramContext* MiniLangParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, MiniLangParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(21); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(20);
      statement();
      setState(23); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1114196) != 0));
    setState(25);
    match(MiniLangParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

MiniLangParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniLangParser::AssignmentContext* MiniLangParser::StatementContext::assignment() {
  return getRuleContext<MiniLangParser::AssignmentContext>(0);
}

MiniLangParser::OutputContext* MiniLangParser::StatementContext::output() {
  return getRuleContext<MiniLangParser::OutputContext>(0);
}

MiniLangParser::InputContext* MiniLangParser::StatementContext::input() {
  return getRuleContext<MiniLangParser::InputContext>(0);
}

MiniLangParser::IfStatementContext* MiniLangParser::StatementContext::ifStatement() {
  return getRuleContext<MiniLangParser::IfStatementContext>(0);
}

MiniLangParser::WhileLoopContext* MiniLangParser::StatementContext::whileLoop() {
  return getRuleContext<MiniLangParser::WhileLoopContext>(0);
}

tree::TerminalNode* MiniLangParser::StatementContext::COMMENT() {
  return getToken(MiniLangParser::COMMENT, 0);
}


size_t MiniLangParser::StatementContext::getRuleIndex() const {
  return MiniLangParser::RuleStatement;
}


std::any MiniLangParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::StatementContext* MiniLangParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, MiniLangParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(33);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(27);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(28);
      output();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(29);
      input();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(30);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(31);
      whileLoop();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(32);
      match(MiniLangParser::COMMENT);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

MiniLangParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniLangParser::AssignmentContext::IDENTIFIER() {
  return getToken(MiniLangParser::IDENTIFIER, 0);
}

MiniLangParser::ExpressionContext* MiniLangParser::AssignmentContext::expression() {
  return getRuleContext<MiniLangParser::ExpressionContext>(0);
}

tree::TerminalNode* MiniLangParser::AssignmentContext::SEPARATOR() {
  return getToken(MiniLangParser::SEPARATOR, 0);
}


size_t MiniLangParser::AssignmentContext::getRuleIndex() const {
  return MiniLangParser::RuleAssignment;
}


std::any MiniLangParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::AssignmentContext* MiniLangParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 4, MiniLangParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(35);
    match(MiniLangParser::IDENTIFIER);
    setState(36);
    match(MiniLangParser::T__0);
    setState(37);
    expression(0);
    setState(38);
    match(MiniLangParser::SEPARATOR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OutputContext ------------------------------------------------------------------

MiniLangParser::OutputContext::OutputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniLangParser::OutputContext::LPAREN() {
  return getToken(MiniLangParser::LPAREN, 0);
}

tree::TerminalNode* MiniLangParser::OutputContext::STRING() {
  return getToken(MiniLangParser::STRING, 0);
}

tree::TerminalNode* MiniLangParser::OutputContext::RPAREN() {
  return getToken(MiniLangParser::RPAREN, 0);
}

tree::TerminalNode* MiniLangParser::OutputContext::SEPARATOR() {
  return getToken(MiniLangParser::SEPARATOR, 0);
}


size_t MiniLangParser::OutputContext::getRuleIndex() const {
  return MiniLangParser::RuleOutput;
}


std::any MiniLangParser::OutputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitOutput(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::OutputContext* MiniLangParser::output() {
  OutputContext *_localctx = _tracker.createInstance<OutputContext>(_ctx, getState());
  enterRule(_localctx, 6, MiniLangParser::RuleOutput);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    match(MiniLangParser::T__1);
    setState(41);
    match(MiniLangParser::LPAREN);
    setState(42);
    match(MiniLangParser::STRING);
    setState(43);
    match(MiniLangParser::RPAREN);
    setState(44);
    match(MiniLangParser::SEPARATOR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InputContext ------------------------------------------------------------------

MiniLangParser::InputContext::InputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniLangParser::InputContext::IDENTIFIER() {
  return getToken(MiniLangParser::IDENTIFIER, 0);
}

tree::TerminalNode* MiniLangParser::InputContext::LPAREN() {
  return getToken(MiniLangParser::LPAREN, 0);
}

tree::TerminalNode* MiniLangParser::InputContext::STRING() {
  return getToken(MiniLangParser::STRING, 0);
}

tree::TerminalNode* MiniLangParser::InputContext::RPAREN() {
  return getToken(MiniLangParser::RPAREN, 0);
}

tree::TerminalNode* MiniLangParser::InputContext::SEPARATOR() {
  return getToken(MiniLangParser::SEPARATOR, 0);
}


size_t MiniLangParser::InputContext::getRuleIndex() const {
  return MiniLangParser::RuleInput;
}


std::any MiniLangParser::InputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitInput(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::InputContext* MiniLangParser::input() {
  InputContext *_localctx = _tracker.createInstance<InputContext>(_ctx, getState());
  enterRule(_localctx, 8, MiniLangParser::RuleInput);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(46);
    match(MiniLangParser::IDENTIFIER);
    setState(47);
    match(MiniLangParser::T__0);
    setState(48);
    match(MiniLangParser::T__2);
    setState(49);
    match(MiniLangParser::LPAREN);
    setState(50);
    match(MiniLangParser::STRING);
    setState(51);
    match(MiniLangParser::RPAREN);
    setState(52);
    match(MiniLangParser::SEPARATOR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

MiniLangParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniLangParser::ConditionContext* MiniLangParser::IfStatementContext::condition() {
  return getRuleContext<MiniLangParser::ConditionContext>(0);
}

std::vector<tree::TerminalNode *> MiniLangParser::IfStatementContext::LBRACE() {
  return getTokens(MiniLangParser::LBRACE);
}

tree::TerminalNode* MiniLangParser::IfStatementContext::LBRACE(size_t i) {
  return getToken(MiniLangParser::LBRACE, i);
}

std::vector<tree::TerminalNode *> MiniLangParser::IfStatementContext::RBRACE() {
  return getTokens(MiniLangParser::RBRACE);
}

tree::TerminalNode* MiniLangParser::IfStatementContext::RBRACE(size_t i) {
  return getToken(MiniLangParser::RBRACE, i);
}

std::vector<MiniLangParser::StatementContext *> MiniLangParser::IfStatementContext::statement() {
  return getRuleContexts<MiniLangParser::StatementContext>();
}

MiniLangParser::StatementContext* MiniLangParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<MiniLangParser::StatementContext>(i);
}


size_t MiniLangParser::IfStatementContext::getRuleIndex() const {
  return MiniLangParser::RuleIfStatement;
}


std::any MiniLangParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::IfStatementContext* MiniLangParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 10, MiniLangParser::RuleIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(54);
    match(MiniLangParser::T__3);
    setState(55);
    condition(0);
    setState(56);
    match(MiniLangParser::LBRACE);
    setState(60);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1114196) != 0)) {
      setState(57);
      statement();
      setState(62);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(63);
    match(MiniLangParser::RBRACE);
    setState(73);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniLangParser::T__4) {
      setState(64);
      match(MiniLangParser::T__4);
      setState(65);
      match(MiniLangParser::LBRACE);
      setState(69);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1114196) != 0)) {
        setState(66);
        statement();
        setState(71);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(72);
      match(MiniLangParser::RBRACE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileLoopContext ------------------------------------------------------------------

MiniLangParser::WhileLoopContext::WhileLoopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniLangParser::ConditionContext* MiniLangParser::WhileLoopContext::condition() {
  return getRuleContext<MiniLangParser::ConditionContext>(0);
}

tree::TerminalNode* MiniLangParser::WhileLoopContext::LBRACE() {
  return getToken(MiniLangParser::LBRACE, 0);
}

tree::TerminalNode* MiniLangParser::WhileLoopContext::RBRACE() {
  return getToken(MiniLangParser::RBRACE, 0);
}

std::vector<MiniLangParser::StatementContext *> MiniLangParser::WhileLoopContext::statement() {
  return getRuleContexts<MiniLangParser::StatementContext>();
}

MiniLangParser::StatementContext* MiniLangParser::WhileLoopContext::statement(size_t i) {
  return getRuleContext<MiniLangParser::StatementContext>(i);
}


size_t MiniLangParser::WhileLoopContext::getRuleIndex() const {
  return MiniLangParser::RuleWhileLoop;
}


std::any MiniLangParser::WhileLoopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitWhileLoop(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::WhileLoopContext* MiniLangParser::whileLoop() {
  WhileLoopContext *_localctx = _tracker.createInstance<WhileLoopContext>(_ctx, getState());
  enterRule(_localctx, 12, MiniLangParser::RuleWhileLoop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    match(MiniLangParser::T__5);
    setState(76);
    condition(0);
    setState(77);
    match(MiniLangParser::LBRACE);
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1114196) != 0)) {
      setState(78);
      statement();
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(84);
    match(MiniLangParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

MiniLangParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniLangParser::ExpressionContext::getRuleIndex() const {
  return MiniLangParser::RuleExpression;
}

void MiniLangParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoubleExprContext ------------------------------------------------------------------

tree::TerminalNode* MiniLangParser::DoubleExprContext::DOUBLE() {
  return getToken(MiniLangParser::DOUBLE, 0);
}

MiniLangParser::DoubleExprContext::DoubleExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any MiniLangParser::DoubleExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitDoubleExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivExprContext ------------------------------------------------------------------

std::vector<MiniLangParser::ExpressionContext *> MiniLangParser::MulDivExprContext::expression() {
  return getRuleContexts<MiniLangParser::ExpressionContext>();
}

MiniLangParser::ExpressionContext* MiniLangParser::MulDivExprContext::expression(size_t i) {
  return getRuleContext<MiniLangParser::ExpressionContext>(i);
}

tree::TerminalNode* MiniLangParser::MulDivExprContext::MUL() {
  return getToken(MiniLangParser::MUL, 0);
}

tree::TerminalNode* MiniLangParser::MulDivExprContext::DIV() {
  return getToken(MiniLangParser::DIV, 0);
}

MiniLangParser::MulDivExprContext::MulDivExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any MiniLangParser::MulDivExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitMulDivExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarExprContext ------------------------------------------------------------------

tree::TerminalNode* MiniLangParser::VarExprContext::IDENTIFIER() {
  return getToken(MiniLangParser::IDENTIFIER, 0);
}

MiniLangParser::VarExprContext::VarExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any MiniLangParser::VarExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitVarExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntExprContext ------------------------------------------------------------------

tree::TerminalNode* MiniLangParser::IntExprContext::INT() {
  return getToken(MiniLangParser::INT, 0);
}

MiniLangParser::IntExprContext::IntExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any MiniLangParser::IntExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitIntExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

tree::TerminalNode* MiniLangParser::ParenExprContext::LPAREN() {
  return getToken(MiniLangParser::LPAREN, 0);
}

MiniLangParser::ExpressionContext* MiniLangParser::ParenExprContext::expression() {
  return getRuleContext<MiniLangParser::ExpressionContext>(0);
}

tree::TerminalNode* MiniLangParser::ParenExprContext::RPAREN() {
  return getToken(MiniLangParser::RPAREN, 0);
}

MiniLangParser::ParenExprContext::ParenExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any MiniLangParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpExprContext ------------------------------------------------------------------

std::vector<MiniLangParser::ExpressionContext *> MiniLangParser::ExpExprContext::expression() {
  return getRuleContexts<MiniLangParser::ExpressionContext>();
}

MiniLangParser::ExpressionContext* MiniLangParser::ExpExprContext::expression(size_t i) {
  return getRuleContext<MiniLangParser::ExpressionContext>(i);
}

tree::TerminalNode* MiniLangParser::ExpExprContext::EXP() {
  return getToken(MiniLangParser::EXP, 0);
}

MiniLangParser::ExpExprContext::ExpExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any MiniLangParser::ExpExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitExpExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubExprContext ------------------------------------------------------------------

std::vector<MiniLangParser::ExpressionContext *> MiniLangParser::AddSubExprContext::expression() {
  return getRuleContexts<MiniLangParser::ExpressionContext>();
}

MiniLangParser::ExpressionContext* MiniLangParser::AddSubExprContext::expression(size_t i) {
  return getRuleContext<MiniLangParser::ExpressionContext>(i);
}

tree::TerminalNode* MiniLangParser::AddSubExprContext::ADD() {
  return getToken(MiniLangParser::ADD, 0);
}

tree::TerminalNode* MiniLangParser::AddSubExprContext::SUB() {
  return getToken(MiniLangParser::SUB, 0);
}

MiniLangParser::AddSubExprContext::AddSubExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any MiniLangParser::AddSubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitAddSubExpr(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::ExpressionContext* MiniLangParser::expression() {
   return expression(0);
}

MiniLangParser::ExpressionContext* MiniLangParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MiniLangParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  MiniLangParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, MiniLangParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(94);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniLangParser::LPAREN: {
        _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(87);
        match(MiniLangParser::LPAREN);
        setState(88);
        expression(0);
        setState(89);
        match(MiniLangParser::RPAREN);
        break;
      }

      case MiniLangParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<VarExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(91);
        match(MiniLangParser::IDENTIFIER);
        break;
      }

      case MiniLangParser::INT: {
        _localctx = _tracker.createInstance<IntExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(92);
        match(MiniLangParser::INT);
        break;
      }

      case MiniLangParser::DOUBLE: {
        _localctx = _tracker.createInstance<DoubleExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(93);
        match(MiniLangParser::DOUBLE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(107);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(105);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(96);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(97);
          antlrcpp::downCast<MulDivExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MiniLangParser::MUL

          || _la == MiniLangParser::DIV)) {
            antlrcpp::downCast<MulDivExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(98);
          expression(8);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(99);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(100);
          antlrcpp::downCast<AddSubExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MiniLangParser::ADD

          || _la == MiniLangParser::SUB)) {
            antlrcpp::downCast<AddSubExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(101);
          expression(7);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ExpExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(102);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(103);
          match(MiniLangParser::EXP);
          setState(104);
          expression(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(109);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

MiniLangParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniLangParser::ExpressionContext *> MiniLangParser::ConditionContext::expression() {
  return getRuleContexts<MiniLangParser::ExpressionContext>();
}

MiniLangParser::ExpressionContext* MiniLangParser::ConditionContext::expression(size_t i) {
  return getRuleContext<MiniLangParser::ExpressionContext>(i);
}

MiniLangParser::RelopContext* MiniLangParser::ConditionContext::relop() {
  return getRuleContext<MiniLangParser::RelopContext>(0);
}

std::vector<MiniLangParser::ConditionContext *> MiniLangParser::ConditionContext::condition() {
  return getRuleContexts<MiniLangParser::ConditionContext>();
}

MiniLangParser::ConditionContext* MiniLangParser::ConditionContext::condition(size_t i) {
  return getRuleContext<MiniLangParser::ConditionContext>(i);
}


size_t MiniLangParser::ConditionContext::getRuleIndex() const {
  return MiniLangParser::RuleCondition;
}


std::any MiniLangParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}


MiniLangParser::ConditionContext* MiniLangParser::condition() {
   return condition(0);
}

MiniLangParser::ConditionContext* MiniLangParser::condition(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MiniLangParser::ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, parentState);
  MiniLangParser::ConditionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, MiniLangParser::RuleCondition, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(117);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniLangParser::IDENTIFIER:
      case MiniLangParser::INT:
      case MiniLangParser::DOUBLE:
      case MiniLangParser::LPAREN: {
        setState(111);
        expression(0);
        setState(112);
        relop();
        setState(113);
        expression(0);
        break;
      }

      case MiniLangParser::T__6: {
        setState(115);
        match(MiniLangParser::T__6);
        setState(116);
        condition(3);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(127);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(125);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ConditionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCondition);
          setState(119);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(120);
          match(MiniLangParser::T__7);
          setState(121);
          condition(3);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ConditionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCondition);
          setState(122);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(123);
          match(MiniLangParser::T__8);
          setState(124);
          condition(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(129);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

MiniLangParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniLangParser::RelopContext::getRuleIndex() const {
  return MiniLangParser::RuleRelop;
}


std::any MiniLangParser::RelopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniLangVisitor*>(visitor))
    return parserVisitor->visitRelop(this);
  else
    return visitor->visitChildren(this);
}

MiniLangParser::RelopContext* MiniLangParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 18, MiniLangParser::RuleRelop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 64512) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool MiniLangParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 7: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);
    case 8: return conditionSempred(antlrcpp::downCast<ConditionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MiniLangParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);
    case 2: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool MiniLangParser::conditionSempred(ConditionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 2);
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void MiniLangParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  minilangParserInitialize();
#else
  ::antlr4::internal::call_once(minilangParserOnceFlag, minilangParserInitialize);
#endif
}
