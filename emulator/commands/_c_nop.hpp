#include "../command/command.hpp"
#include "../runtime/runtime.hpp"

class NOP : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 0;
    }

    int getLength() override
    {
        return 0;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override
    {
        return 0;
    }
};