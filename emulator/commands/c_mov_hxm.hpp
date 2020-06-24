#ifndef C_MOV_HXM_HPP
#define C_MOV_HXM_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_HXM : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 148;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_hxm <aa>
    {
        runtime->getHX()->setValueComplete16bit(runtime->getMemory()->get16bitValueFromAddress(ppt8_std::combine_8bit_to_16bit(args[0], args[1])));
        return 0;
    }
};

#endif