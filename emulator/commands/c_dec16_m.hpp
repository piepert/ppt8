#ifndef C_Dec16_M_HPP
#define C_Dec16_M_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Dec16_M : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 87;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // inc16_m <aa>
    {
        runtime->getMemory()->set16Value(args[0], runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1]))-1);
        return 0;
    }
};

#endif