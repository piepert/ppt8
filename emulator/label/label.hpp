#ifndef EMULATOR_LABEL_HPP
#define EMULATOR_LABEL_HPP


#include <cstdint>

class Label
{
private:
    uint16_t start_pos;      // var   label
    uint16_t end_pos;        // #var  #label

public:
    Label(uint16_t start, uint16_t end);

    uint16_t getPos();
    uint16_t getFollowingAddress();
};


#endif //EMULATOR_LABEL_HPP
