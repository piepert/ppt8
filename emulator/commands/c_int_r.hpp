#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"

class Int_R : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 34;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // int reg
    {
        return ppt8_std::functions::interrupt(runtime->getRegisterByID(args[0])->getLower8bit(), runtime);
    }
};