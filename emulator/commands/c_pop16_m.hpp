#ifndef C_POP16_M_HPP
#define C_POP16_M_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Pop16_M : public Command
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

    int run(std::vector<uint8_t> args, Runtime* runtime) override // pop16_m <aa>
    {
        uint8_t lower = runtime->getStack()->top();
        runtime->getStack()->pop();

        uint8_t higher = runtime->getStack()->top();
        runtime->getStack()->pop();

        runtime->getMemory()->set16Value(ppt8_std::combine_8bit_to_16bit(args[0], args[1]), ppt8_std::combine_8bit_to_16bit(higher, lower));
        return 0;
    }
};

#endif