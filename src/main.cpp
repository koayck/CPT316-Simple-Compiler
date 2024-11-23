/**
 * @file main.cpp
 * @brief Main program file for the MiniLang compiler/interpreter
 * 
 * This file contains the main program logic for processing MiniLang source files.
 * It handles:
 * 1. File input/output operations
 * 2. Orchestration of the compilation/interpretation pipeline
 * 3. Error reporting
 * 4. AST (Abstract Syntax Tree) visualization
 */

#include <iostream>
#include <vector>
#include "Lexer.cpp"
#include "Parser.cpp"
#include "AST.h"
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * @brief Helper function to print text with indentation
 * 
 * Used for creating a hierarchical visual representation of the AST.
 * Each level of the tree is indented by a specified number of spaces.
 * 
 * @param text The text to be printed
 * @param indent Number of spaces to indent
 */
void printIndented(const string &text, int indent)
{
  cout << string(indent, ' ') << text << endl;
}

/**
 * @brief Recursively prints the Abstract Syntax Tree
 * 
 * This function implements a visitor pattern to traverse and visualize the AST.
 * It handles different types of statements:
 * - Assignment statements (variable = expression)
 * - Print statements (print expression)
 * - Input statements (variable = r("prompt"))
 * - If statements (with optional else branches)
 * - While statements (loops)
 * - Type declarations (with optional initialization)
 * 
 * @param stmt Pointer to the statement node in the AST
 * @param indent Current indentation level
 */
void printAST(const StmtPtr &stmt, int indent = 0)
{
  // Handle Assignment Statements
  if (auto assignStmt = dynamic_pointer_cast<AssignmentStmt>(stmt))
  {
    printIndented("AssignmentStmt", indent);
    printIndented("|-- Variable: " + assignStmt->name.lexeme, indent + 4);
    printIndented("|-- Value: " + assignStmt->value->toString(), indent + 4);
  }
  // Handle Print Statements
  else if (auto printStmt = dynamic_pointer_cast<PrintStmt>(stmt))
  {
    printIndented("PrintStmt", indent);
    printIndented("|-- Expression: " + printStmt->expression->toString(), indent + 4);
  }
  // Handle Input Statements
  else if (auto inputStmt = dynamic_pointer_cast<InputStmt>(stmt))
  {
    printIndented("InputStmt", indent);
    printIndented("|-- Variable: " + inputStmt->name.lexeme, indent + 4);
    printIndented("|-- Prompt: \"" + inputStmt->prompt.lexeme + "\"", indent + 4);
  }
  // Handle If Statements
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
  // Handle While Statements
  else if (auto whileStmt = dynamic_pointer_cast<WhileStmt>(stmt))
  {
    printIndented("WhileStmt", indent);
    printIndented("|-- Condition: " + whileStmt->condition->toString(), indent + 4);
    printIndented("|-- Body:", indent + 4);
    printAST(whileStmt->body, indent + 8);
  }
  // Handle Type Declaration Statements
  else if (auto declStmt = dynamic_pointer_cast<TypeDeclarationStmt>(stmt))
  {
    printIndented("TypeDeclarationStmt", indent);
    printIndented("|-- Type: " + declStmt->type.lexeme, indent + 4);
    printIndented("|-- Name: " + declStmt->name.lexeme, indent + 4);
    if (declStmt->inputStmt) {
      auto input = dynamic_pointer_cast<InputStmt>(declStmt->inputStmt);
      printIndented("|-- Input:", indent + 4);
      printIndented("|-- Prompt: \"" + input->prompt.lexeme + "\"", indent + 8);
    }
    else if (declStmt->initializer)
    {
      printIndented("|-- Initializer: " + declStmt->initializer->toString(), indent + 4);
    }
  }
}

/**
 * @brief Main program entry point
 * 
 * Program flow:
 * 1. Prompts user for input file name
 * 2. Reads source code from file
 * 3. Performs lexical analysis (tokenization)
 * 4. Performs syntactic analysis (parsing)
 * 5. Displays tokens and AST
 * 6. Handles any errors that occur during processing
 * 
 * Example usage:
 * - Basic variable declaration: int x = 5;
 * - Input with prompt: x = r("Enter value: ");
 * - Typed input: int y = r("Enter y: ");
 * 
 * @return int Exit status (0 for success, 1 for error)
 */
int main()
{
  // Get input file name from user
  string inputFile;
  cout << "Enter the input file name: ";
  cin >> inputFile;

  inputFile = "input/" + inputFile;

  // Open and read the source file
  ifstream file(inputFile);

  if (!file.is_open())
  {
    cerr << "Error opening file: " << inputFile << endl;
    return 1;
  }

  // Read file contents into string
  string line;
  string input;
  while (getline(file, line))
  {
    input += line + "\n";
  }

  try
  {
    // Phase 1: Lexical Analysis
    // Convert source code into tokens
    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    // Display tokens for debugging/visualization
    cout << "=== Tokens ===" << endl;
    for (const auto &token : tokens)
    {
      cout << token << endl;
    }

    cout << "\n=== Parse Tree ===" << endl;

    // Phase 2: Syntactic Analysis
    // Convert tokens into Abstract Syntax Tree
    vector<StmtPtr> statements = parse(tokens);

    // Display AST for debugging/visualization
    cout << "\n=== Abstract Syntax Tree ===" << endl;
    for (const auto &statement : statements)
    {
      printAST(statement);
      cout << endl; // Add blank line between top-level statements
    }
  }
  catch (const runtime_error &e)
  {
    // Error handling: Display error message and exit
    cerr << "Error: " << e.what() << endl;
    return 1;
  }

  file.close();
  return 0;
}