#ifndef C_MOV_IRV_HPP
#define C_MOV_IRV_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_IRV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 133;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_irv @<r>, <v>
    {
        runtime->getMemory()->setValue(runtime->getRegisterByID(args[0])->getComplete16bit(), args[1]);
        return 0;
    }
};

#endif