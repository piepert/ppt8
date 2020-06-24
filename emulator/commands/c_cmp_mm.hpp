#ifndef C_CMP_MM_HPP
#define C_CMP_MM_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Cmp_MM : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 149;
    }

    int getLength() override
    {
        return 4;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // cmp_mm <aa>, <aa>
    {
        runtime->getHX()->setValueComplete16bit(ppt8_std::functions::compare(runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])), runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[2], args[3]))));
        return 0;
    }
};

#endif