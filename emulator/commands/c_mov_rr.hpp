#ifndef EMULATOR_C_MOV_RR_HPP
#define EMULATOR_C_MOV_RR_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_RR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 1;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_rr <r>, <r>
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getRegisterByID(args[1])->getComplete16bit());
        return 0;
    }
};

#endif //EMULATOR_C_MOV_RR_HPP
