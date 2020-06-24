#ifndef C_PUSH16_M_HPP
#define C_PUSH16_M_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Push16_M : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 41;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // push16_m <aa>
    {
        runtime->push16bitSplittet(runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])));
        return 0;
    }
};

#endif