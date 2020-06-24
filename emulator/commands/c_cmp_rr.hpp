#ifndef EMULATOR_C_CMP_RR_HPP
#define EMULATOR_C_CMP_RR_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Cmp_RR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 151;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // cmp_sm <sreg>, <vv>
    {
        runtime->getHX()->setValueComplete16bit(ppt8_std::functions::compare(runtime->getRegisterByID(args[0])->getComplete16bit(), runtime->getRegisterByID(args[1])->getComplete16bit()));
        return 0;
    }
};

#endif //EMULATOR_C_CMP_RR_HPP
