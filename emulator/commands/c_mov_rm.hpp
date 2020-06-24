#ifndef EMULATOR_C_MOV_RM_HPP
#define EMULATOR_C_MOV_RM_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_RM : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 11;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_rm <r>, <a>
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[1], args[2])));
        return 0;
    }
};

#endif //EMULATOR_C_MOV_RM_HPP
