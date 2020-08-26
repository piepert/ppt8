#ifndef EMULATOR_STD_HPP
#define EMULATOR_STD_HPP

#include <cstdint>
#include <string>
#include "../runtime/runtime.hpp"

namespace ppt8_std {
    uint16_t combine_8bit_to_16bit(uint8_t high, uint8_t low);
    uint8_t get_higher_8bit_from_16bit(uint16_t val);
    uint8_t get_lower_8bit_from_16bit(uint16_t val);
    char get_char();
    void clrscr(Runtime* runtime);

    int run_command(uint8_t command, int* index, Runtime* runtime);
}

#endif //EMULATOR_STD_HPP
