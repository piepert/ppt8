#ifndef C_ADD_RS_HPP
#define C_ADD_RS_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Add_RS : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 53;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // COMMAND
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getRegisterByID(args[0])->getComplete16bit() + runtime->getSubRegisterByID(args[1]));
        return 0;
    }
};

#endif