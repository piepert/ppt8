#ifndef EMULATOR_C_CMP_SS_HPP
#define EMULATOR_C_CMP_SS_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Cmp_SS : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 150;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // cmp_ss <sreg>, <sreg>
    {
        runtime->getHX()->setValueComplete16bit(ppt8_std::functions::compare(runtime->getSubRegisterByID(args[0]), runtime->getSubRegisterByID(args[1])));
        return 0;
    }
};

#endif //EMULATOR_C_CMP_SS_HPP
