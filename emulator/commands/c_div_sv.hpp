#ifndef C_DIV_SV_HPP
#define C_DIV_SV_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Div_SV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 79;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // COMMAND
    {
        runtime->setSubRegisterByID(args[0], runtime->getSubRegisterByID(args[0]) / args[1]);
        runtime->getFX()->setValueComplete16bit(runtime->getSubRegisterByID(args[0]) % args[1]);
        return 0;
    }
};

#endif