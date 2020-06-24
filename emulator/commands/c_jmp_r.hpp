#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"

class Jmp_R : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 94;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override
    {
        runtime->PROGRAMM_INDEX = runtime->getRegisterByID(args[0])->getComplete16bit() - 1;
        return 0;
    }
};