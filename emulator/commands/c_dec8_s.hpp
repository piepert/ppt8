#ifndef C_DEC8_S_HPP
#define C_DEC8_S_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Dec8_S : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 84;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // dec8_s <s>
    {
        runtime->setSubRegisterByID(args[0], runtime->getSubRegisterByID(args[0])-1);
        return 0;
    }
};

#endif