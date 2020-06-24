#ifndef C_MOV_MIR_HPP
#define C_MOV_MIR_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_MIR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 136;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_mir <aa>, @<r>
    {
        runtime->getMemory()->setValue(ppt8_std::combine_8bit_to_16bit(args[0], args[1]), runtime->getMemory()->getValueFromAddress(runtime->getRegisterByID(args[2])->getComplete16bit()));
        return 0;
    }
};

#endif