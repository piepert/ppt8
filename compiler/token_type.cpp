#include "token_type.hpp"
#include "ppt8_std.hpp"
#include "runtime.hpp"

TokenType TokenType::determineType(std::string token, int line, Runtime* runtime)
{
    // c - commands
    // v - byte
    // n - name
    // label_def - label definition
    // r - register
    // s - subregister
    // @ - @/address

    if (is_number(token))
    {
        if (std::stoi(token) > 255)
            return TokenType("vv");
        else
            return TokenType("v");
    }
    else if (token.size() > 2)
    {
        if (token == "word")
            return TokenType("word");
        else if (token.substr(0, 2) == "0x")
        {
            if ((token.size()-2) / 2 > 1)
                return TokenType("vv");
            else
                return TokenType("v");
        }
        else if (token.substr(0, 2) == "0b")
        {
            if ((token.size()-2) / 8 > 1)
                return TokenType("vv");
            else
                return TokenType("v");
        }
        else if (token.substr(0, 2) == "0d")
        {
            if (!is_number(token.substr(2, token.size())))
            {
                std::cout << "error in line " << line << ": invalid decimal number \"" << token << "\"." << std::endl;
                exit(1);
            }

            if (std::stoi(token.substr(2, token.size())) > 255)
                return TokenType("vv");
            else
                return TokenType("v");
        }
    }

    if (runtime->existsNameByValue(token))
    {
        if (runtime->getNameByValue(token)->getType() == NT_Command)
            return TokenType("c");
        else if (runtime->getNameByValue(token)->getType() == NT_Register)
            return TokenType("r");
        else if (runtime->getNameByValue(token)->getType() == NT_Subregister)
            return TokenType("s");
        else if (runtime->getNameByValue(token)->getType() == NT_Label)
            return TokenType("wordvv");
        else if (runtime->getNameByValue(token)->getType() == NT_Variable)
            return TokenType("vv");
        else                                        // else it has to be label
            return TokenType("wordvv");
    }

    if (token == "~")
        return TokenType("s_len");

    if (token == "db")
        return TokenType("db");

    std::cout << "error in line " << line << ": unknown token \"" << token << "\"." << std::endl;
    exit(1);
}

std::string TokenType::getPattern()
{
    return this->pattern;
}

TokenType::TokenType() {}

TokenType::TokenType(std::string pattern)
{
    this->pattern = pattern;
}

std::string TokenType::makeValue(std::string raw_value)
{
    std::string ret = raw_value;
    return ret;
}
