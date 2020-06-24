#ifndef C_CALL_HPP
#define C_CALL_HPP

#include <string>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Call : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 15;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // call <vv>
    {
        runtime->getStack()->push(ppt8_std::get_higher_8bit_from_16bit(runtime->PROGRAMM_INDEX));
        runtime->getStack()->push(ppt8_std::get_lower_8bit_from_16bit(runtime->PROGRAMM_INDEX));

        if (runtime->DEBUG)
        {
            std::cout << "((CALL " << (int) ppt8_std::combine_8bit_to_16bit(args[0], args[1]) << std::endl;
        }

        runtime->PROGRAMM_INDEX = (int) ppt8_std::combine_8bit_to_16bit(args[0], args[1]) - 1;
        return 0;
    }
};

#endif