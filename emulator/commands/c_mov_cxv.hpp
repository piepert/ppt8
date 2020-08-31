#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_CXV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 18;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_cxv <v²>
    {
        uint16_t v = ppt8_std::combine_8bit_to_16bit(args[0], args[1]);
        runtime->getCX()->setValueComplete16bit(v);
        return 0;
    }
};