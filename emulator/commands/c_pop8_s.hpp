#ifndef C_POP8_S_HPP
#define C_POP8_S_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Pop8_S : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 43;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // pop8_s <s>
    {
        runtime->setSubRegisterByID(args[0], runtime->getStack()->top());
        runtime->getStack()->pop();
        return 0;
    }
};

#endif