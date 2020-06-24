#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"

class Int_V : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 33;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override
    {
        return ppt8_std::functions::interrupt(args[0], runtime);
    }
};