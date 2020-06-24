#include "label.hpp"

Label::Label(uint16_t start, uint16_t end)
{
    this->start_pos = start;
    this->end_pos = end;
}

uint16_t Label::getPos()
{
    return start_pos;
}

uint16_t Label::getFollowingAddress()
{
    return end_pos;
}
