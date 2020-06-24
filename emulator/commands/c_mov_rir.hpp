#ifndef C_MOV_RIR_HPP
#define C_MOV_RIR_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_RIR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 134;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_rir <r>, @<r>
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getMemory()->get16bitValueFromAddress(runtime->getRegisterByID(args[1])->getComplete16bit()));
        return 0;
    }
};

#endif