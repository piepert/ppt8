#ifndef C_CMP_SV_HPP
#define C_CMP_SV_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Cmp_SV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 91;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // cmp_sm <sreg>, <v>
    {
        if (runtime->DEBUG)
            std::cout << "((CMP " << (int) runtime->getSubRegisterByID(args[0]) << " & " << (int) args[1] << "))" << std::endl;

        runtime->getHX()->setValueComplete16bit(ppt8_std::functions::compare(runtime->getSubRegisterByID(args[0]), args[1]));
        return 0;
    }
};

#endif