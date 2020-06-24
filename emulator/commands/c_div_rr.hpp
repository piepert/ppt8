#ifndef C_DIV_RR_HPP
#define C_DIV_RR_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Div_RR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 72;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // add_rr <r>, <r>
    {
        runtime->getRegisterByID(args[0])->setValueComplete16bit(runtime->getRegisterByID(args[0])->getComplete16bit() / runtime->getRegisterByID(args[1])->getComplete16bit());
        runtime->getFX()->setValueComplete16bit(runtime->getRegisterByID(args[0])->getComplete16bit() % runtime->getRegisterByID(args[1])->getComplete16bit());
        return 0;
    }
};

#endif