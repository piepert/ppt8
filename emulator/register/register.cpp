#include "register.hpp"
#include "../std/std.hpp"

uint8_t Register::getHigher8bit()
{
    return this->high;
}

uint8_t Register::getLower8bit()
{
    return this->low;
}

uint16_t Register::getComplete16bit()
{
    return ppt8_std::combine_8bit_to_16bit(this->high, this->low);
}

void Register::setValueLower8bit(uint8_t lower)
{
    this->low = lower;
}

void Register::setValueHigher8bit(uint8_t higher)
{
    this->high = higher;
}

void Register::setValueComplete16bit(uint16_t complete)
{
    this->high = ppt8_std::get_higher_8bit_from_16bit(complete);
    this->low = ppt8_std::get_lower_8bit_from_16bit(complete);
}
