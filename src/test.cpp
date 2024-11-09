#include <iostream>
#include <fstream>
#include <sstream>
#include "SimpleLexer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source-file>" << std::endl;
        return 1;
    }

    // Read the input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    // Create an instance of SimpleLexer with the input string
    SimpleLexer lexer(input);

    // Tokenize the input string
    std::vector<Token> tokens = lexer.tokenize();

    // Process and print the tokens
    for (const Token &token : tokens) {
        std::cout << "Token Type: " << tokenTypeToString(token.type) << ", Value: " << token.value << std::endl;
    }

    return 0;
}