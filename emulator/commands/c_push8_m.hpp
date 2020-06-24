#ifndef C_PUSH8_M_HPP
#define C_PUSH8_M_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Push8_M : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 38;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // push8_m <aa>
    {
        runtime->push8bit(runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])));
        return 0;
    }
};

#endif