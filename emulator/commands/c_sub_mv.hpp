#ifndef C_SUB_MV_HPP
#define C_SUB_MV_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Sub_MV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 60;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // COMMAND
    {
        runtime->getMemory()->set16Value(ppt8_std::combine_8bit_to_16bit(args[0], args[1]), runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])) - args[2]);
        return 0;
    }
};

#endif