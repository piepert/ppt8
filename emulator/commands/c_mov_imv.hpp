#ifndef EMULATOR_C_MOV_IMV_HPP
#define EMULATOR_C_MOV_IMV_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_IMV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 9;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_imv <a1 a2>, <v>
    {
        uint16_t addr = ppt8_std::combine_8bit_to_16bit(args[0], args[1]);
        runtime->getMemory()->setValue(runtime->getMemory()->get16bitValueFromAddress(addr), args[2]);
        return 0;
    }
};

#endif //EMULATOR_C_MOV_IMV_HPP
