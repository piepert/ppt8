#include "name.hpp"

Name::Name(std::string value, NameType type)
{
    this->value = value;
    this->type = type;
}

std::string Name::getValue() const
{
    return this->value;
}

void Name::setValue(std::string value)
{
    this->value = value;
}

NameType Name::getType() const
{
    return this->type;
}

void Name::setType(NameType type)
{
    this->type = type;
}
