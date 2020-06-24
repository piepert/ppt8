#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Mov_GXV : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 22;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_gxv <v²>
    {
        uint8_t v = ppt8_std::combine_8bit_to_16bit(args[0], args[1]);
        runtime->getGX()->setValueComplete16bit(v);
        return 0;
    }
};