#include <iostream>
#include <iomanip>
#include "std.hpp"
#include "../command/command.hpp"
#include "../tstring.hpp"

#include "tr.hpp"

uint16_t ppt8_std::combine_8bit_to_16bit(uint8_t high, uint8_t low)
{
    return (high << 8) | (low & 0xff);
}

uint8_t ppt8_std::get_higher_8bit_from_16bit(uint16_t val)
{
    return (val >> 8) & 0xff;
}

uint8_t ppt8_std::get_lower_8bit_from_16bit(uint16_t val)
{
    return val & 0xff;
}

/*
 * run_command error codes:
 *
 *  -1   - unknown error
 *  2    - unknown command (ignored, no error)
 */

std::vector<int> hexstr_to_ints(std::string hex)
{
    std::vector<int> ret;

    for (int i = 0; i < hex.size(); i += 2)
    {
        std::string num = hex[i]+std::string("")+hex[i+1];
        int x = 0;
        sscanf(num.c_str(), "%x", &x);
        ret.push_back(x);
    }

    return ret;
}

int ppt8_std::run_command(uint8_t command, int* index, Runtime* runtime)
{
    if (!runtime->existsCommand(command))
        return 2;

    std::vector<uint8_t> args;
    int count = 0;

    while (count < runtime->getCommand(command)->getLength())
    {
        (*index)++;
        count++;

        args.push_back(runtime->getMemory()->getValueFromAddress(*index));
    }

    if (runtime->DEBUG)
    {
        std::cout << std::endl;
        std::cout << "AX=" << std::hex << (int) runtime->getAX()->getComplete16bit()
                  << " BX=" << (int) runtime->getBX()->getComplete16bit()
                  << " CX=" << (int) runtime->getCX()->getComplete16bit()
                  << " DX=" << (int) runtime->getDX()->getComplete16bit() << std::endl;

        std::cout << "EX=" << std::hex << (int) runtime->getEX()->getComplete16bit()
                  << " FX=" << (int) runtime->getFX()->getComplete16bit()
                  << " GX=" << (int) runtime->getGX()->getComplete16bit()
                  << " HX=" << (int) runtime->getHX()->getComplete16bit() << std::endl;

        std::cout << "[" << std::setw(3) << std::hex << runtime->PROGRAMM_INDEX << std::dec << " ]  " << std::hex << (int) command << std::dec << " ";
        std::string str;
        std::stringstream sstr;

        for (auto i : args)
        {
            sstr << std::setw(2) << std::hex << ((i < 17) ? "0" : "") << (int) i << std::dec << " ";
            str = sstr.str();

            while (str.size() < 20)
                str += " ";
        }

        std::cout << str << "     ";

        str = disassemble_opcode(command);
        while (str.size() < 8)
            str += " ";
        std::cout << str << "    ";

        for (auto i : args)
        {
            if (i < 17)
                std::cout << 0;
            std::cout << std::hex << (int) i << std::dec << " ";
        }

        std::cout << std::endl;
        std::string line;

        while (line != "c" && line != "continue")
        {
            std::cout << "> ";
            std::getline(std::cin, line);

            std::vector<tri::string> args = tri::string(line).split(" ");

            if (args.size() >= 1)
            {
                if (args[0] == "q" || args[0] == "quit")
                    exit(0);
                else if (args[0] == "mt") // memory taktout from n to m: mt <n> <m>
                {
                    if (args.size() == 3)
                    {
                        try
                        {
                            int from = std::stoi(args[1].cxs());
                            int to = std::stoi(args[2].cxs());

                            if (args[1].startsWith("0x")) // Parse hex number
                            {
                                from = hexstr_to_ints(args[1].replace("0x", "").cxs())[0];
                                // std::cout << "HEX: " << from << std::endl;
                                to = hexstr_to_ints(args[2].replace("0x", "").cxs())[0];
                                // std::cout << "HEX: " << to << std::endl;
                            }

                            line = "";

                            std::string spaces = "";
                            while (std::to_string(from).size()+spaces.size() < std::to_string(to).size())
                                spaces += " ";
                            std::cout << std::endl << from << spaces << " |  ";

                            for (int i = from; i <= to; i++)
                            {
                                int v = runtime->getMemory()->getValueFromAddress(i);

                                if (i % 8 == 0)
                                {
                                    spaces = "";
                                    std::cout << "    " << line;

                                    spaces = "";
                                    while (std::to_string(from+i).size()+spaces.size() < std::to_string(to).size())
                                        spaces += " ";

                                    std::cout << std::endl << from+i << spaces << " |  ";
                                    line = "";
                                }

                                if ((int) v < 17)
                                    std::cout << "0";
                                std::cout << std::hex << v << " ";

                                if ((int) v > 32)
                                    line += (char) v;
                                else
                                    line += ".";
                            }

                            spaces = "";
                            std::cout << "    " << line;

                            spaces = "";
                            while (std::to_string(to).size()+spaces.size() < std::to_string(to).size())
                                spaces += " ";

                            std::cout << std::endl << to << spaces << " |  ";
                            line = "";

                            std::cout << std::endl;

                            //for (int i = from; i <= to; i++)
                            //    std::cout << std::hex << (runtime->getMemory()->getValueFromAddress(i) < 16 ? "0" : "")  << (int) runtime->getMemory()->getValueFromAddress(i) << " " << std::dec << (i % 8 == 0 && i-from != 0 ? "\n" : "");
                        }
                        catch (std::exception ex)
                        {
                            std::cout << "syntax error." << std::endl;
                        }
                    }
                    else if (args.size() == 2)
                    {
                        int addr = 0;

                        try
                        {
                            if (args[1].startsWith("0x")) // Parse hex number
                                addr = hexstr_to_ints(args[1].replace("0x", "").cxs())[0];
                            else
                                addr = std::stoi(args[1].cxs());

                            std::cout << (int) runtime->getMemory()->getValueFromAddress(addr) << std::hex << " | 0x" << (int) runtime->getMemory()->getValueFromAddress(addr) << std::dec << std::endl;
                        }
                        catch (std::exception ex)
                        {
                            std::cout << "syntax error." << std::endl;
                        }
                    }
                    else
                        std::cout << "syntax error." << std::endl;
                }
                else if (args[0] == "jmp")
                {

                }
                else
                    line = "continue";
            }
        }
    }

    return runtime->getCommand(command)->run(args, runtime);
}

#if (defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) || defined(__DJGPP__)) && !defined(__CYGWIN__)
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
char __getchar()
{
    char buf = 0;
    struct termios old = {0};

    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");

    if (read(0, &buf, 1) < 0)
        perror("read()");

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    return (buf);
}
#endif

char ppt8_std::get_char()
{
    std::cin.sync();
#ifdef __DJGPP__
    return getch();
#else
    return __getchar();
#endif
}

void ppt8_std::clrscr(Runtime* runtime)
{
    runtime->clearPixels();

#ifdef __DJGPP__
    system("cls");
#else
    system("clear");
#endif
}
