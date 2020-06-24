#ifndef EMULATOR_FUNCTIONS_HPP
#define EMULATOR_FUNCTIONS_HPP

#include <cstdint>
#include "../runtime/runtime.hpp"

#define IMMEDIATE 1
#define MEM_ADDRESS 0

namespace ppt8_std
{
    namespace functions
    {
        int print_char(uint8_t c);
        int interrupt(uint8_t code, Runtime* runtime);
        int compare(int a, int b);
    }
}

#endif //EMULATOR_FUNCTIONS_HPP
