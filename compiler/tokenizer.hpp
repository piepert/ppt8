#ifndef COMPILER_TOKENIZER_HPP
#define COMPILER_TOKENIZER_HPP


#include <vector>
#include "token.hpp"

class Tokenizer
{
public:
    static std::vector<Token> tokenize(std::string code, Runtime* runtime);
    static int strLen(std::string str);
};


#endif //COMPILER_TOKENIZER_HPP
