#ifndef C_MUL_RR_HPP
#define C_MUL_RR_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mul_RR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 64;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mul_rr <r>, <r>
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getRegisterByID(args[0])->getComplete16bit() * runtime->getRegisterByID(args[1])->getComplete16bit());
        return 0;
    }
};

#endif