#include "memory.hpp"
#include "../std/std.hpp"

void Memory::fillUntilAddress(uint16_t address)
{
    while (this->memory.size() < address+1)
        memory.push_back(0);
}

void Memory::setValue(uint16_t address, uint8_t value)
{
    if (this->memory.size() < address+1)
        this->fillUntilAddress(address);

    memory[address] = value;
}

uint8_t Memory::getValueFromAddress(uint16_t address)
{
    if (this->memory.size() < address+1)
        return 0;

    return memory[address];
}

uint16_t Memory::get16bitValueFromAddress(uint16_t address)
{
    if (address+2 > this->memory.size())
        return 0;

    return ppt8_std::combine_8bit_to_16bit(memory[address], memory[address+1]);
}

void Memory::set16Value(uint16_t address, uint16_t value)
{
    if (this->memory.size() < address+2)
        this->fillUntilAddress(address+1);

    memory[address] = ppt8_std::get_higher_8bit_from_16bit(value);
    memory[address+1] = ppt8_std::get_lower_8bit_from_16bit(value);
}
