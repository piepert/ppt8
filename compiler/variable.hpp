#ifndef COMPILER_VARIABLE_HPP
#define COMPILER_VARIABLE_HPP

#include <string>

class Variable
{
private:
    std::string value;
    std::string name;

public:
    Variable(std::string name, std::string value);

    std::string getName() const;
    void setName(std::string name);

    std::string getValue() const;
    void setValue(std::string value);
};


#endif //COMPILER_VARIABLE_HPP
