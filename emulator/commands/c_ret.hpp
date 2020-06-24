#ifndef C_RET_HPP
#define C_RET_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Ret : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 47;
    }

    int getLength() override
    {
        return 0;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // ret
    {
        uint8_t a1 = runtime->getStack()->top();
        runtime->getStack()->pop(); // lower bits

        uint8_t a2 = runtime->getStack()->top();
        runtime->getStack()->pop(); // higher bits

        runtime->PROGRAMM_INDEX = (int) ppt8_std::combine_8bit_to_16bit(a2, a1);
        return 0;
    }
};

#endif