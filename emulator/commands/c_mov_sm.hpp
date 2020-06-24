#ifndef EMULATOR_C_MOV_SM_HPP
#define EMULATOR_C_MOV_SM_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_SM : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 13;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_sm <sr>, <v1 v2>
    {
        runtime->setSubRegisterByID(args[0], runtime->getMemory()->getValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[1], args[2])));
        return 0;
    }
};

#endif //EMULATOR_C_MOV_SM_HPP
