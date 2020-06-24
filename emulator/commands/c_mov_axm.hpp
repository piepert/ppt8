#ifndef C_MOV_AXM_HPP
#define C_MOV_AXM_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_AXM : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 141;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_axv <aa>
    {
        runtime->getAX()->setValueComplete16bit(runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])));
        return 0;
    }
};

#endif