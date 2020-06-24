#ifndef C_CMP_MV_HPP
#define C_CMP_MV_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Cmp_MV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 90;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // cmp_rm <aa>, <v>
    {
        runtime->getHX()->setValueComplete16bit(ppt8_std::functions::compare(runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])), args[2]));
        return 0;
    }
};

#endif