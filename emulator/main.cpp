#include <iostream>
#include <fstream>

#include "runtime/runtime.hpp"
#include "std/std.hpp"

#include "commands/c_int_v.hpp"

int main(int argc, char* argv[])
{
    Runtime runtime = Runtime();

    bool debug = false;
    std::string file;
    std::string code;

    if (argc == 2)
    {
        if (argv[1] != "debug")
            file = argv[1];
        else
        {
            std::cout << "error: syntax for \"debug\"-mode: ppt8e debug <binary>" << std::endl;
            return 1;
        }
    }
    else if (argc == 3)
    {
        debug = true;
        file = argv[2];
    }
    else
    {
        std::cout << "error: syntax: ppt8e [debug] <binary>" << std::endl;
        return 1;
    }

    runtime.DEBUG = debug;
    std::fstream bin;
    bin.open(file, std::ios::in | std::ios::binary);

    if (!bin.good())
    {
        std::cout << "error: file \"" << file << "\" not found." << std::endl;

        if (!debug)
            return 1;
    }

    code = std::string((std::istreambuf_iterator<char>(bin)), std::istreambuf_iterator<char>());

    std::cout << "Press enter to start the programm...";
    ppt8_std::get_char();
    ppt8_std::clrscr();

    runtime.PROGRAMM_CODE = code;

    for (int* i = &runtime.PROGRAMM_INDEX; *i < runtime.PROGRAMM_CODE.size(); runtime.PROGRAMM_INDEX++)
        ppt8_std::run_command(code[*i], &runtime.PROGRAMM_CODE, i, &runtime);

    return 0;
}
