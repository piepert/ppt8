#ifndef C_PUSH16_R_HPP
#define C_PUSH16_R_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Push16_R : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 40;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // push16_r <r>
    {
        runtime->push16bitSplittet(runtime->getRegisterByID(args[0])->getComplete16bit());
        return 0;
    }
};

#endif