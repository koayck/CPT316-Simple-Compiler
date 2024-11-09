#include <iostream>
#include <vector>
#include "Lexer.cpp"

using namespace std;

int main()
{
  cout << "Enter your code: " << endl;
  string input;

  getline(cin, input);

  Lexer lexer(input);
  vector<Token> tokens = lexer.tokenize(); // Ensure the Lexer class is properly defined and linked

  for (const auto &token : tokens)
  {
    cout << "Token Type: " << tokenTypeToString(token.type)
         << ", Value: " << token.lexeme << endl;
  }

  return 0;
}