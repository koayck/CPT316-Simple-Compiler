#include <iostream>
#include "SimpleLexer.h"
#include "SimpleLexer.cpp"

int main() {
    // Example input string
    std::string input = R"(
        int x = 10;
        double y = 20.5;
        string s = "Hello, World!";
        # This is a comment
        x = x + y * 2;
        @
    )";

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