#ifndef C_MUL_RM_HPP
#define C_MUL_RM_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mul_RM : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 66;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // add_rm r, aa
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getRegisterByID(args[0])->getComplete16bit() * runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[1], args[2])));
        return 0;
    }
};

#endif