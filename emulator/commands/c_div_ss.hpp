#ifndef C_DIV_SS_HPP
#define C_DIV_SS_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Div_SS : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 140;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mul_ss <s>, <s>
    {
        runtime->setSubRegisterByID(args[0], runtime->getSubRegisterByID(args[0]) / runtime->getSubRegisterByID(args[1]));
        runtime->setSubRegisterByID(16, runtime->getSubRegisterByID(args[0]) % runtime->getSubRegisterByID(args[1]));
        return 0;
    }
};

#endif