#ifndef C_ADD_RV_HPP
#define C_ADD_RV_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Add_RV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 49;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // add_rv r, vv
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getRegisterByID(args[0])->getComplete16bit() + ppt8_std::combine_8bit_to_16bit(args[1], args[2]));
        return 0;
    }
};

#endif