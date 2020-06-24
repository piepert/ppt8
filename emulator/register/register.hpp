#ifndef EMULATOR_REGISTER_HPP
#define EMULATOR_REGISTER_HPP

#include <cstdint>

class Register
{
    // 11001000   00100110 -> 1100100000100110
    // high bits  low bits -> complete bits

    uint8_t high;
    uint8_t low;

public:
    uint8_t getLower8bit();
    uint8_t getHigher8bit();
    uint16_t getComplete16bit();

    void setValueLower8bit(uint8_t lower);
    void setValueHigher8bit(uint8_t higher);
    void setValueComplete16bit(uint16_t complete);
};


#endif //EMULATOR_REGISTER_HPP
