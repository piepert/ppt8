#ifndef COMPILER_TOKEN_TYPE_HPP
#define COMPILER_TOKEN_TYPE_HPP

#include <string>
#include "runtime.hpp"

class TokenType
{
private:
    std::string pattern;

public:
    TokenType();
    TokenType(std::string pattern);

    static TokenType determineType(std::string token, int line, Runtime* runtime);
    std::string getPattern();

    static std::string makeValue(std::string raw_value);
};


#endif //COMPILER_TOKEN_TYPE_HPP
