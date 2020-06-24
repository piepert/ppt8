#ifndef C_POP16_R_HPP
#define C_POP16_R_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Pop16_R : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 45;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // pop16_r <r>
    {
        runtime->getRegisterByID(args[0])->setValueLower8bit(runtime->getStack()->top());
        runtime->getStack()->pop();

        runtime->getRegisterByID(args[0])->setValueHigher8bit(runtime->getStack()->top());
        runtime->getStack()->pop();

        return 0;
    }
};

#endif