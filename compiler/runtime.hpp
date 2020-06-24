#ifndef COMPILER_RUNTIME_HPP
#define COMPILER_RUNTIME_HPP

#include <vector>
#include "name.hpp"
#include "variable.hpp"

class Runtime
{
private:
    std::vector<Name> names;
    std::vector<Variable> variables;

public:
    Runtime();

    void registerName(Name n);
    bool existsNameByValue(std::string value);
    Name* getNameByValue(std::string value);

    void addVariable(Variable v);
    bool existsVariableByName(std::string name);
    Variable* getVariableByName(std::string name);
};


#endif //COMPILER_RUNTIME_HPP
