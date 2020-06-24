#ifndef C_CMP_RV_HPP
#define C_CMP_RV_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Cmp_RV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 92;
    }

    int getLength() override
    {
        return 3;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // cmp_sm <sreg>, <vv>
    {
        if (runtime->DEBUG)
            std::cout << "((CMP " << (int) runtime->getRegisterByID(args[0])->getComplete16bit() << " & " << (int) ppt8_std::combine_8bit_to_16bit(args[1], args[2]) << "))" << std::endl;

        runtime->getHX()->setValueComplete16bit(ppt8_std::functions::compare(runtime->getRegisterByID(args[0])->getComplete16bit(), ppt8_std::combine_8bit_to_16bit(args[1], args[2])));
        return 0;
    }
};

#endif