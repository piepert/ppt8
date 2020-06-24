#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Alloc : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 32;
    }

    int getLength() override
    {
        return 4;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // alloc <a²>, <l²> <data...>
    {
        std::vector<uint8_t> data;
        uint16_t address = ppt8_std::combine_8bit_to_16bit(args[0], args[1]);
        uint16_t len = ppt8_std::combine_8bit_to_16bit(args[2], args[3]);

        if (runtime->DEBUG)
            std::cout << "((ALLOC " << (int) address << " to " << (int) address+len << ":";

        std::string line = "";
        int i;

        for (i = 0; i < len; i++)
        {
            runtime->getMemory()->setValue(address+i, runtime->PROGRAMM_CODE[++runtime->PROGRAMM_INDEX]);

            if (runtime->DEBUG)
            {
                if (i % 8 == 0)
                {
                    std::string spaces = "";
                    std::cout << "    " << line;

                    spaces = "";
                    while (std::to_string(address+i).size()+spaces.size() < std::to_string(address+len).size())
                        spaces += " ";

                    std::cout << std::endl << address+i << spaces << " |  ";
                    line = "";
                }

                if ((int) runtime->PROGRAMM_CODE[runtime->PROGRAMM_INDEX] < 17)
                    std::cout << "0";
                std::cout << std::hex << (int) runtime->PROGRAMM_CODE[runtime->PROGRAMM_INDEX] << " ";

                if ((int) runtime->PROGRAMM_CODE[runtime->PROGRAMM_INDEX] > 32)
                    line += (char) runtime->PROGRAMM_CODE[runtime->PROGRAMM_INDEX];
                else
                    line += ".";
            }
        }

        if (runtime->DEBUG)
        {
            if (line.size() != 0)
            {
                std::string spaces = "";

                while ((i % 8)*3+spaces.size() < 24)
                    spaces += " ";

                std::cout << "    " << spaces << line;
            }

            std::cout << std::endl << "ALLOC))" << std::endl;
        }

        return 0;
    }
};