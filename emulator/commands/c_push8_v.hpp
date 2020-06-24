#ifndef C_PUSH8_V_HPP
#define C_PUSH8_V_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Push8_V : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 39;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // push8_V <aa>
    {
        runtime->push8bit(args[0]);
        return 0;
    }
};

#endif