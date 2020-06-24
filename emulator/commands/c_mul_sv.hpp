#ifndef C_MUL_SV_HPP
#define C_MUL_SV_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mul_SV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 71;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // COMMAND
    {
        runtime->setSubRegisterByID(args[0], runtime->getSubRegisterByID(args[0]) * args[1]);
        return 0;
    }
};

#endif