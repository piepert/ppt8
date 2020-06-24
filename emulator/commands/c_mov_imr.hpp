#ifndef EMULATOR_C_MOV_IMR_HPP
#define EMULATOR_C_MOV_IMR_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_IMR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 12;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_imr <a1 a2>, <r>
    {
        uint16_t addr = ppt8_std::combine_8bit_to_16bit(args[0], args[1]);
        addr = runtime->getMemory()->get16bitValueFromAddress(addr);

        runtime->getMemory()->setValue(addr, runtime->getRegisterByID(args[2])->getLower8bit());
        runtime->getMemory()->setValue(addr, runtime->getRegisterByID(args[2])->getHigher8bit());
        return 0;
    }
};

#endif //EMULATOR_C_MOV_IMR_HPP
