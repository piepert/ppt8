#ifndef C_MOV_SIR_HPP
#define C_MOV_SIR_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_SIR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 135;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_sir <r>, @<r>
    {
        runtime->setSubRegisterByID(args[0], runtime->getMemory()->getValueFromAddress(runtime->getRegisterByID(args[1])->getComplete16bit()));
        return 0;
    }
};

#endif