#include "variable.hpp"

Variable::Variable(std::string name, std::string value)
{
    this->name = name;
    this->value = value;
}

std::string Variable::getName() const
{
    return this->name;
}

void Variable::setName(std::string name)
{
    this->name = name;
}

std::string Variable::getValue() const
{
    return this->value;
}

void Variable::setValue(std::string value)
{
    this->value = value;
}
