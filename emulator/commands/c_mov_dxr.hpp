#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"

class Mov_DXR : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 27;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // mov_bxv <reg>
    {
        runtime->getDX()->setValueComplete16bit(runtime->getRegisterByID(args[0])->getComplete16bit());
        return 0;
    }
};