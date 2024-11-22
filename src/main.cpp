#include <iostream>
#include <vector>
#include "Lexer.cpp"
#include "Parser.cpp"
#include <fstream>
#include <iomanip>

using namespace std;

// Helper function to print indented text
void printIndented(const string &text, int indent)
{
  cout << string(indent, ' ') << text << endl;
}

// Function to print AST in a tree-like structure
void printAST(const StmtPtr &stmt, int indent = 0)
{
  if (auto assignStmt = dynamic_pointer_cast<AssignmentStmt>(stmt))
  {
    printIndented("AssignmentStmt", indent);
    printIndented("|-- Variable: " + assignStmt->name.lexeme, indent + 4);
    printIndented("|-- Value: " + assignStmt->value->toString(), indent + 4);
  }
  else if (auto printStmt = dynamic_pointer_cast<PrintStmt>(stmt))
  {
    printIndented("PrintStmt", indent);
    printIndented("|-- Expression: " + printStmt->expression->toString(), indent + 4);
  }
  else if (auto inputStmt = dynamic_pointer_cast<InputStmt>(stmt))
  {
    printIndented("InputStmt", indent);
    printIndented("|-- Variable: " + inputStmt->name.lexeme, indent + 4);
  }
  else if (auto ifStmt = dynamic_pointer_cast<IfStmt>(stmt))
  {
    printIndented("IfStmt", indent);
    printIndented("|-- Condition: " + ifStmt->condition->toString(), indent + 4);
    printIndented("|-- Then Branch:", indent + 4);
    printAST(ifStmt->thenBranch, indent + 8);
    if (ifStmt->elseBranch)
    {
      printIndented("|-- Else Branch:", indent + 4);
      printAST(ifStmt->elseBranch, indent + 8);
    }
  }
  else if (auto whileStmt = dynamic_pointer_cast<WhileStmt>(stmt))
  {
    printIndented("WhileStmt", indent);
    printIndented("|-- Condition: " + whileStmt->condition->toString(), indent + 4);
    printIndented("|-- Body:", indent + 4);
    printAST(whileStmt->body, indent + 8);
  }
  else if (auto declStmt = dynamic_pointer_cast<TypeDeclarationStmt>(stmt))
  {
    printIndented("TypeDeclarationStmt", indent);
    printIndented("|-- Type: " + declStmt->type.lexeme, indent + 4);
    printIndented("|-- Name: " + declStmt->name.lexeme, indent + 4);
    if (declStmt->initializer)
    {
      printIndented("|-- Initializer: " + declStmt->initializer->toString(), indent + 4);
    }
  }
}

int main()
{
  // prompt user for input file
  string inputFile;
  cout << "Enter the input file name: ";
  cin >> inputFile;

  inputFile = "input/" + inputFile;

  // read from a text file
  ifstream file(inputFile);

  if (!file.is_open())
  {
    cerr << "Error opening file: " << inputFile << endl;
    return 1;
  }

  string line;
  string input;

  while (getline(file, line))
  {
    input += line + "\n";
  }

  try
  {
    // Lexical Analysis (Tokenization)
    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    cout << "=== Tokens ===" << endl;
    for (const auto &token : tokens)
    {
      cout << token << endl;
    }

    cout << "\n=== Parse Tree ===" << endl;

    // Syntactic Analysis (Parsing)
    vector<StmtPtr> statements = parse(tokens);

    cout << "\n=== Abstract Syntax Tree ===" << endl;
    for (const auto &statement : statements)
    {
      printAST(statement);
      cout << endl; // Add blank line between top-level statements
    }
  }
  catch (const runtime_error &e)
  {
    cerr << "Error: " << e.what() << endl;
    return 1;
  }

  file.close();
  return 0;
}