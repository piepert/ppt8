#ifndef C_MOV_IRR_HPP
#define C_MOV_IRR_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_IRR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 132;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_irr @<r>, <r>
    {
        runtime->getMemory()->set16Value(runtime->getRegisterByID(args[0])->getComplete16bit(), runtime->getRegisterByID(args[1])->getComplete16bit());
        return 0;
    }
};

#endif