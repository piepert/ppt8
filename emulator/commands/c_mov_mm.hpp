#ifndef EMULATOR_C_MOV_MM_HPP
#define EMULATOR_C_MOV_MM_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_MM : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 8;
    }

    int getLength() override
    {
        return 4;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_mm <d1 d2>, <a1 a2>
    {
        uint16_t addr1 = ppt8_std::combine_8bit_to_16bit(args[0], args[1]);
        uint16_t addr2 = ppt8_std::combine_8bit_to_16bit(args[2], args[3]);

        runtime->getMemory()->setValue(addr1, runtime->getMemory()->getValueFromAddress(addr2));
        return 0;
    }
};

#endif //EMULATOR_C_MOV_MM_HPP
