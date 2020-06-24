#ifndef EMULATOR_C_MOV_MS_HPP
#define EMULATOR_C_MOV_MS_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_MS : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 5;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_ms <a>, <r>
    {
        runtime->getMemory()->setValue(ppt8_std::combine_8bit_to_16bit(args[0], args[1]), runtime->getSubRegisterByID(args[2]));
        return 0;
    }
};

#endif //EMULATOR_C_MOV_MS_HPP
