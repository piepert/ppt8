#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"

class Mov_AXV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 16;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_axv <v²>
    {
        uint16_t v = ppt8_std::combine_8bit_to_16bit(args[0], args[1]);
        runtime->getAX()->setValueComplete16bit(v);
        return 0;
    }
};