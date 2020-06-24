#ifndef C_PUSH8_S_HPP
#define C_PUSH8_S_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Push8_S : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 37;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // push8_s <v>
    {
        runtime->getStack()->push(runtime->getSubRegisterByID(args[0]));
        return 0;
    }
};

#endif