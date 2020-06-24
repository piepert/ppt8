#ifndef C_DIV_MR_HPP
#define C_DIV_MR_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Div_MR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 75;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // COMMAND
    {
        runtime->getMemory()->set16Value(ppt8_std::combine_8bit_to_16bit(args[0], args[1]), runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])) / runtime->getRegisterByID(args[2])->getComplete16bit());
        runtime->getFX()->setValueComplete16bit(runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])) % runtime->getRegisterByID(args[2])->getComplete16bit());
        return 0;
    }
};

#endif