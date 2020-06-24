#ifndef C_INC8_M_HPP
#define C_INC8_M_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Inc8_M : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 81;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // inc8_m <aa>
    {
        runtime->getMemory()->setValue(args[0], runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1]))+1);
        return 0;
    }
};

#endif