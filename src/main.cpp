#include <iostream>
#include <vector>
#include "Lexer.cpp"
#include "Parser.cpp"
#include <fstream>

using namespace std;

int main()
{
  // set the input file
  string inputFile = "input/test.txt";

  // read from a text file
  ifstream file(inputFile);

  if (!file.is_open())
  {
    cerr << "Error opening file: " << inputFile << endl;
    return 1; // Exit with an error code
  }

  string line;
  string input;

  while (getline(file, line))
  {
    input += line + "\n";
  }

  // Lexical Analysis
  Lexer lexer(input);
  vector<Token> tokens = lexer.tokenize();

  cout << "Tokens: " << endl;

  for (const auto &token : tokens)
  {
    cout << "Token Type: " << tokenTypeToString(token.type)
         << ", Value: " << token.lexeme << endl;
  }

  cout << endl;
  cout << endl;

  // Syntactic Analysis (Parsing)
  Parser parser(tokens);
  vector<StmtPtr> statements = parser.parse();

  cout << "Statements: " << endl;

  // After parsing
  for (const auto &statement : statements)
  {
    cout << statement->toString() << endl; // Print the AST representation
  }

  if (file.is_open())
    file.close();

  return 0;
}