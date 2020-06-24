#ifndef C_DIV_MS_HPP
#define C_DIV_MS_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Div_MS : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 78;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // COMMAND
    {
        runtime->getMemory()->setValue(ppt8_std::combine_8bit_to_16bit(args[0], args[1]), runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])) / runtime->getSubRegisterByID(args[2]));
        runtime->getFX()->setValueComplete16bit(runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])) % runtime->getSubRegisterByID(args[2]));
        return 0;
    }
};

#endif