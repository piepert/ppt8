#include "token.hpp"

Token::Token(std::string value, TokenType type, int line, int line_index)
{
    this->value = value;
    this->type = type;
    this->line = line;
    this->line_index = line_index;
}

std::string Token::getValue() const
{
    return this->value;
}

TokenType Token::getType() const
{
    return this->type;
}

int Token::getLine() const
{
    return this->line;
}

int Token::getLineIndex() const
{
    return this->line_index;
}
