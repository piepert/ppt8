#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"

class Int_S : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 35;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override
    {
        return ppt8_std::functions::interrupt(runtime->getSubRegisterByID(args[0]), runtime);
    }
};