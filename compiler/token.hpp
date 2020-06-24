#ifndef COMPILER_TOKEN_HPP
#define COMPILER_TOKEN_HPP

#include <string>
#include "token_type.hpp"

class Token
{
private:
    std::string value;
    TokenType type;
    int line;
    int line_index;

public:
    Token(std::string value, TokenType type, int line, int line_index);

    std::string getValue() const;
    TokenType getType() const;
    int getLine() const;
    int getLineIndex() const;
};


#endif //COMPILER_TOKEN_HPP
