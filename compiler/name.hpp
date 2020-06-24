#ifndef COMPILER_NAME_HPP
#define COMPILER_NAME_HPP

#include <string>

enum NameType
{
    NT_Variable,
    NT_Label,
    NT_Command,
    NT_Register,
    NT_Subregister
};

class Name
{
private:
    NameType type;
    std::string value;

public:
    Name(std::string value, NameType type);

    std::string getValue() const;
    void setValue(std::string value);

    NameType getType() const;
    void setType(NameType type);
};


#endif //COMPILER_NAME_HPP
