#ifndef EMULATOR_C_MOV_IRM_HPP
#define EMULATOR_C_MOV_IRM_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_IRM : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 10;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_irm <reg>, <a1 a2> ; loads 8bit-value from address a to address in register r
    {
        runtime->getMemory()->setValue(runtime->getRegisterByID(args[0])->getComplete16bit(), runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[2], args[3])));
        return 0;
    }
};

#endif //EMULATOR_C_MOV_IRM_HPP
