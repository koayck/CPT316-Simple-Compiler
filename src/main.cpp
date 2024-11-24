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

void printTokens(const vector<Token>& tokens);

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
    string inputFile;
    cout << "Enter the input file name: ";
    cin >> inputFile;

    inputFile = "input/" + inputFile;
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
        // Phase 1: Lexical Analysis
        Lexer lexer(input);
        vector<Token> tokens = lexer.tokenize();
        printTokens(tokens);

        // Phase 2: Syntactic Analysis
        cout << "Syntax Analysis:" << endl;
        vector<StmtPtr> statements = parse(tokens);
        
        // Display AST using the parser's AST creation function
        cout << createCompleteASTString(statements);
    }
    catch (const runtime_error &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    file.close();
    return 0;
}