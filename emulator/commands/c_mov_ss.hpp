#ifndef EMULATOR_C_MOV_SS_HPP
#define EMULATOR_C_MOV_SS_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_SS : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 4;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_rv <sr>, <sr>
    {
        runtime->setSubRegisterByID(args[0], runtime->getSubRegisterByID(args[1]));
        return 0;
    }
};

#endif //EMULATOR_C_MOV_SS_HPP
