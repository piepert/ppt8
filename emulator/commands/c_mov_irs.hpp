#ifndef EMULATOR_C_MOV_IRS_HPP
#define EMULATOR_C_MOV_IRS_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_IRS : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 14;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_irs <reg>, <sreg> ; move sreg to address stored in reg
    {
        runtime->getMemory()->setValue(runtime->getRegisterByID(args[0])->getComplete16bit(), runtime->getSubRegisterByID(args[1]));
        return 0;
    }
};

#endif //EMULATOR_C_MOV_IRS_HPP
