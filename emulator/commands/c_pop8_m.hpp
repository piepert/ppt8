#ifndef C_POP8_M_HPP
#define C_POP8_M_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Pop8_M : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 44;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // pop8_s <aa>
    {
        runtime->getMemory()->setValue(ppt8_std::combine_8bit_to_16bit(args[0], args[1]), runtime->getStack()->top());
        runtime->getStack()->pop();
        return 0;
    }
};

#endif