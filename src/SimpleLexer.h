/**
 * @file SimpleLexer.h
 * @brief Defines the SimpleLexer class and related structures for tokenizing input strings.
 */

#pragma once

#include <string>
#include <vector>

using namespace std;

/**
 * @enum TokenType
 * @brief Represents the different types of tokens that can be identified by the lexer.
 */
enum class TokenType
{
    IDENTIFIER, ///< An identifier (variable name, function name, etc.)
    INT,        ///< An integer number
    DOUBLE,     ///< A double-precision floating-point number
    STRING,     ///< A string literal
    COMMENT,    ///< A comment
    WS,         ///< Whitespace
    ADD,        ///< Addition operator '+'
    SUB,        ///< Subtraction operator '-'
    MUL,        ///< Multiplication operator '*'
    DIV,        ///< Division operator '/'
    EXP,        ///< Exponentiation operator '^'
    SEPARATOR,  ///< Separator (comma, semicolon, etc.)
    LPAREN,     ///< Left parenthesis '('
    RPAREN,     ///< Right parenthesis ')'
    LBRACE,     ///< Left brace '{'
    RBRACE,     ///< Right brace '}'
    UNKNOWN     ///< Unknown token type
};

/**
 * @struct Token
 * @brief Represents a token identified by the lexer.
 */
struct Token
{
    TokenType type;    ///< The type of the token
    string value; ///< The value of the token as a string
};

/**
 * @class SimpleLexer
 * @brief A simple lexer for tokenizing input strings.
 */
class SimpleLexer
{
public:
    /**
     * @brief Constructs a SimpleLexer with the given input string.
     * @param input The input string to be tokenized.
     */
    explicit SimpleLexer(const string &input);

    /**
     * @brief Tokenizes the input string and returns a vector of tokens.
     * @return A vector of tokens identified in the input string.
     */
    vector<Token> tokenize();

private:
    string input; ///< The input string to be tokenized
    size_t pos;        ///< The current position in the input string

    /**
     * @brief Peeks at the current character without advancing the position.
     * @return The current character.
     */
    char peek() const;

    /**
     * @brief Gets the current character and advances the position.
     * @return The current character.
     */
    char get();

    /**
     * @brief Skips whitespace characters in the input string.
     */
    void skipWhitespace();

    /**
     * @brief Tokenizes an identifier starting at the current position.
     * @return A token representing the identifier.
     */
    Token identifier();

    /**
     * @brief Tokenizes a number starting at the current position.
     * @return A token representing the number.
     */
    Token number();

    /**
     * @brief Tokenizes a string starting at the current position.
     * @return A token representing the string.
     */
    Token string();

    /**
     * @brief Tokenizes a comment starting at the current position.
     * @return A token representing the comment.
     */
    Token comment();
};
/**
 * @brief Converts a TokenType enum value to its corresponding string representation.
 * @param type The TokenType enum value.
 * @return The string representation of the TokenType.
 */
string tokenTypeToString(TokenType type);