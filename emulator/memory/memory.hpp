#ifndef EMULATOR_MEMORY_HPP
#define EMULATOR_MEMORY_HPP

#include <cstdint>
#include <vector>

class Memory
{
private:
    std::vector<uint8_t> memory;

public:
    void fillUntilAddress(uint16_t address);
    void setValue(uint16_t address, uint8_t value);
    void set16Value(uint16_t address, uint16_t value);
    uint8_t getValueFromAddress(uint16_t address);
    uint16_t get16bitValueFromAddress(uint16_t address);
};


#endif //EMULATOR_MEMORY_HPP
