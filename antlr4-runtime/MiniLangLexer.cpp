
// Generated from c:/Users/kck03/Desktop/CPT316-Simple-Compiler/MiniLang.g4 by ANTLR 4.13.1


#include "MiniLangLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct MiniLangLexerStaticData final {
  MiniLangLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MiniLangLexerStaticData(const MiniLangLexerStaticData&) = delete;
  MiniLangLexerStaticData(MiniLangLexerStaticData&&) = delete;
  MiniLangLexerStaticData& operator=(const MiniLangLexerStaticData&) = delete;
  MiniLangLexerStaticData& operator=(MiniLangLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag minilanglexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
MiniLangLexerStaticData *minilanglexerLexerStaticData = nullptr;

void minilanglexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (minilanglexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(minilanglexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MiniLangLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "IDENTIFIER", 
      "INT", "DOUBLE", "STRING", "COMMENT", "WS", "ADD", "SUB", "MUL", "DIV", 
      "EXP", "SEPARATOR", "LPAREN", "RPAREN", "LBRACE", "RBRACE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,31,176,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,3,1,4,1,4,
  	1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,8,1,8,1,8,1,
  	9,1,9,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,
  	1,14,1,15,1,15,5,15,110,8,15,10,15,12,15,113,9,15,1,16,4,16,116,8,16,
  	11,16,12,16,117,1,17,4,17,121,8,17,11,17,12,17,122,1,17,1,17,4,17,127,
  	8,17,11,17,12,17,128,1,18,1,18,5,18,133,8,18,10,18,12,18,136,9,18,1,18,
  	1,18,1,19,1,19,5,19,142,8,19,10,19,12,19,145,9,19,1,19,1,19,1,20,4,20,
  	150,8,20,11,20,12,20,151,1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,24,
  	1,24,1,25,1,25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,29,1,29,1,30,1,30,
  	0,0,31,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,
  	27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,
  	25,51,26,53,27,55,28,57,29,59,30,61,31,1,0,6,3,0,65,90,95,95,97,122,4,
  	0,48,57,65,90,95,95,97,122,1,0,48,57,1,0,34,34,2,0,10,10,13,13,3,0,9,
  	10,13,13,32,32,182,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,
  	9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,
  	0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,
  	0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,
  	41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,
  	0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,
  	0,1,63,1,0,0,0,3,65,1,0,0,0,5,67,1,0,0,0,7,69,1,0,0,0,9,72,1,0,0,0,11,
  	77,1,0,0,0,13,83,1,0,0,0,15,85,1,0,0,0,17,88,1,0,0,0,19,91,1,0,0,0,21,
  	93,1,0,0,0,23,95,1,0,0,0,25,98,1,0,0,0,27,101,1,0,0,0,29,104,1,0,0,0,
  	31,107,1,0,0,0,33,115,1,0,0,0,35,120,1,0,0,0,37,130,1,0,0,0,39,139,1,
  	0,0,0,41,149,1,0,0,0,43,155,1,0,0,0,45,157,1,0,0,0,47,159,1,0,0,0,49,
  	161,1,0,0,0,51,163,1,0,0,0,53,166,1,0,0,0,55,168,1,0,0,0,57,170,1,0,0,
  	0,59,172,1,0,0,0,61,174,1,0,0,0,63,64,5,61,0,0,64,2,1,0,0,0,65,66,5,112,
  	0,0,66,4,1,0,0,0,67,68,5,114,0,0,68,6,1,0,0,0,69,70,5,105,0,0,70,71,5,
  	102,0,0,71,8,1,0,0,0,72,73,5,101,0,0,73,74,5,108,0,0,74,75,5,115,0,0,
  	75,76,5,101,0,0,76,10,1,0,0,0,77,78,5,119,0,0,78,79,5,104,0,0,79,80,5,
  	105,0,0,80,81,5,108,0,0,81,82,5,101,0,0,82,12,1,0,0,0,83,84,5,33,0,0,
  	84,14,1,0,0,0,85,86,5,38,0,0,86,87,5,38,0,0,87,16,1,0,0,0,88,89,5,124,
  	0,0,89,90,5,124,0,0,90,18,1,0,0,0,91,92,5,62,0,0,92,20,1,0,0,0,93,94,
  	5,60,0,0,94,22,1,0,0,0,95,96,5,62,0,0,96,97,5,61,0,0,97,24,1,0,0,0,98,
  	99,5,60,0,0,99,100,5,61,0,0,100,26,1,0,0,0,101,102,5,61,0,0,102,103,5,
  	61,0,0,103,28,1,0,0,0,104,105,5,33,0,0,105,106,5,61,0,0,106,30,1,0,0,
  	0,107,111,7,0,0,0,108,110,7,1,0,0,109,108,1,0,0,0,110,113,1,0,0,0,111,
  	109,1,0,0,0,111,112,1,0,0,0,112,32,1,0,0,0,113,111,1,0,0,0,114,116,7,
  	2,0,0,115,114,1,0,0,0,116,117,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,
  	118,34,1,0,0,0,119,121,7,2,0,0,120,119,1,0,0,0,121,122,1,0,0,0,122,120,
  	1,0,0,0,122,123,1,0,0,0,123,124,1,0,0,0,124,126,5,46,0,0,125,127,7,2,
  	0,0,126,125,1,0,0,0,127,128,1,0,0,0,128,126,1,0,0,0,128,129,1,0,0,0,129,
  	36,1,0,0,0,130,134,5,34,0,0,131,133,8,3,0,0,132,131,1,0,0,0,133,136,1,
  	0,0,0,134,132,1,0,0,0,134,135,1,0,0,0,135,137,1,0,0,0,136,134,1,0,0,0,
  	137,138,5,34,0,0,138,38,1,0,0,0,139,143,5,35,0,0,140,142,8,4,0,0,141,
  	140,1,0,0,0,142,145,1,0,0,0,143,141,1,0,0,0,143,144,1,0,0,0,144,146,1,
  	0,0,0,145,143,1,0,0,0,146,147,6,19,0,0,147,40,1,0,0,0,148,150,7,5,0,0,
  	149,148,1,0,0,0,150,151,1,0,0,0,151,149,1,0,0,0,151,152,1,0,0,0,152,153,
  	1,0,0,0,153,154,6,20,0,0,154,42,1,0,0,0,155,156,5,43,0,0,156,44,1,0,0,
  	0,157,158,5,45,0,0,158,46,1,0,0,0,159,160,5,42,0,0,160,48,1,0,0,0,161,
  	162,5,47,0,0,162,50,1,0,0,0,163,164,5,42,0,0,164,165,5,42,0,0,165,52,
  	1,0,0,0,166,167,5,59,0,0,167,54,1,0,0,0,168,169,5,40,0,0,169,56,1,0,0,
  	0,170,171,5,41,0,0,171,58,1,0,0,0,172,173,5,123,0,0,173,60,1,0,0,0,174,
  	175,5,125,0,0,175,62,1,0,0,0,8,0,111,117,122,128,134,143,151,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  minilanglexerLexerStaticData = staticData.release();
}

}

MiniLangLexer::MiniLangLexer(CharStream *input) : Lexer(input) {
  MiniLangLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *minilanglexerLexerStaticData->atn, minilanglexerLexerStaticData->decisionToDFA, minilanglexerLexerStaticData->sharedContextCache);
}

MiniLangLexer::~MiniLangLexer() {
  delete _interpreter;
}

std::string MiniLangLexer::getGrammarFileName() const {
  return "MiniLang.g4";
}

const std::vector<std::string>& MiniLangLexer::getRuleNames() const {
  return minilanglexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& MiniLangLexer::getChannelNames() const {
  return minilanglexerLexerStaticData->channelNames;
}

const std::vector<std::string>& MiniLangLexer::getModeNames() const {
  return minilanglexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& MiniLangLexer::getVocabulary() const {
  return minilanglexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MiniLangLexer::getSerializedATN() const {
  return minilanglexerLexerStaticData->serializedATN;
}

const atn::ATN& MiniLangLexer::getATN() const {
  return *minilanglexerLexerStaticData->atn;
}




void MiniLangLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  minilanglexerLexerInitialize();
#else
  ::antlr4::internal::call_once(minilanglexerLexerOnceFlag, minilanglexerLexerInitialize);
#endif
}
