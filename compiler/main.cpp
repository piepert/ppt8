#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include "token.hpp"
#include "tokenizer.hpp"
#include "tr.hpp"

int main(int argc, char* argv[])
{
    bool watch = false;

    if (argc != 4 && argc != 5)
    {
        std::cout << "error: wrong syntax." << std::endl;
        std::cout << "syntax: ppt8c <sourcefile> -o <outputfile>" << std::endl;
        return 1;
    }

    if (argc == 5 && std::string(argv[4]) == "-w")
        watch = true;

    if (std::string(argv[2]) != "-o")
    {
        std::cout << "error: wrong syntax: \"" << argv[2] << "\"" << std::endl;
        std::cout << "syntax: ppt8c <sourcefile> -o <outputfile>" << std::endl;
        return 1;
    }

    int cache = 0;
    int lm = 0;

    while (true)
    {
        while (cache == lm)
        {
            struct stat result;
            if(stat(argv[1], &result)==0)
            {
                cache = result.st_mtime;
            }

            usleep(1000000 / 5); // wait 0.2 second
        }

        lm = cache;
        std::cout << "Updated. " << cache << std::endl;
        std::ifstream ifs(argv[1]);

        if (!ifs.is_open())
        {
            std::cout << "error: file \"" << argv[1] << "\" not found." << std::endl;
            return 1;
        }

        std::string str((std::istreambuf_iterator<char>(ifs)),
            std::istreambuf_iterator<char>());

        if (str.size() == 0)
        {
            std::cout << "Ignoring empty file \"" << argv[1] << "\"..." << std::endl << std::endl;
            continue;
        }

        if (str[str.size()-1] != '\n')
            str += '\n';

        Runtime runtime = Runtime();
        std::vector<Token> tokens = Tokenizer::tokenize(str, &runtime);
        std::vector<Token> command;
        std::vector<std::vector<Token>> commands;

        for (const Token &t : tokens)
        {
            if (command.size() > 0 && command[0].getValue() == "db")
            {
                if (t.getType().getPattern() == "new_line")
                    continue;
                else if (t.getType().getPattern() != "v" && t.getType().getPattern() != "vv")
                {
                    if (!command.empty())
                        commands.push_back(command);

                    command.clear();
                    command.push_back(t);
                }
                else
                    command.push_back(t);

                continue;
            }

            if (t.getType().getPattern() == "new_line")
            {
                if (!command.empty())
                    commands.push_back(command);
                command.clear();
            }
            else
                command.push_back(t);
        }

        for (std::vector<Token> &command : commands)
        {
            for (int i = 0; i < command.size(); i++)
            {
                if (command[i].getValue() == "word" || command[i].getValue() == "@")
                {
                    if (command[i].getValue() == "word" && command[i+1].getValue() == "@")
                        continue;
                    if (command[i].getValue() == "@" && command[i+1].getType().getPattern() == "r")
                        continue;

                    if (command.size()-(i+1) < 2 && command[i+1].getType().getPattern() != "vv")
                        command.insert(command.begin()+i+1,
                            Token("0x00", TokenType("v"),
                                command[i].getLine(),
                                command[i].getLineIndex()));

                    else if (command[i+1].getType().getPattern() != "vv" &&
                        command[i+1].getType().getPattern()+command[i+2].getType().getPattern() != "vv")
                        command.insert(command.begin()+i+1,
                            Token("0x00", TokenType("v"),
                                command[i].getLine(),
                                command[i].getLineIndex()));
                }
            }
        }

        std::string output;

        for (std::vector<Token> &command : commands)
        {
            output += "    ";
            if (command[0].getType().getPattern() == "label")
            {
                output += "\n"+command[0].getValue()+":\n";
                continue;
            }
            else if (command[0].getValue() == "db")
            {
                for (int i = 1; i < command.size(); i++)
                    output += command[i].getValue()+" ";
                output += "\n";
            }
            else if (command[0].getValue() == "alloc")
            {
                // syntax: alloc aa, ll, ...
                bool var = command[1].getType().getPattern() == "n" && command[1].getValue() != "word";

                for (int i = 0; i < command.size(); i++)
                {
                    while (command[i].getValue() == "," || command[i].getType().getPattern() == "word")
                        command.erase(command.begin()+i);
                }

                output += "alloc ";

                int i = 1;
                if (var) // alloc n,a,l,... ; alloc n,@a,l,...
                {
                    if (command.size() <= 5)
                    {
                        std::cout << "error in line " << command[i].getLine() << ": wrong alloc syntax." << std::endl;

                        if (!watch)
                            exit(1);
                        continue;
                    }

                    runtime.addVariable(Variable(command[i].getValue(),
                        command[i+1].getValue()+" "+command[i+2].getValue()));
                    i++;
                }

                if (command[i+2].getValue() == "~")
                {
                    std::string len = std::to_string(Tokenizer::strLen(command[i+3].getValue()));

                    if (TokenType::determineType(len, command[0].getLine(), &runtime).getPattern() == "v")
                        len = "0x00 "+len;

                    output += command[i].getValue()+" "+command[i+1].getValue() + ", "+len+", ";
                    i += 3;
                }
                else
                {
                    output += command[i].getValue()+" "+
                        command[i+1].getValue() + ", "+
                        command[i+2].getValue()+" "+
                        command[i+3].getValue()+", ";

                    i += 4;
                }

                for (; i < command.size(); i++)
                    output += (command[i].getType().getPattern() == "s" ? "\"" : "") +
                        command[i].getValue() +
                        (command[i].getType().getPattern() == "s" ? "\"" : "") + " ";

                output += "\n";
                // alloc a,l,...
                continue;
            }
            else
            {
                std::string mnemonic = get_mnemonic_for_pattern(command);
                output += mnemonic+" ";

                if (mnemonic == "null")
                {
                    std::cout << "error in line " << command[0].getLine() <<
                        ": incorrect combination of instruction and arguments. (" << create_pattern(command) << ")" << std::endl;

                    if (!watch)
                        exit(1);
                    continue;
                }

                int i = 1;

                if (mnemonic == "mov_axv" ||
                    mnemonic == "mov_bxv" ||
                    mnemonic == "mov_cxv" ||
                    mnemonic == "mov_dxv" ||
                    mnemonic == "mov_exv" ||
                    mnemonic == "mov_fxv" ||
                    mnemonic == "mov_gxv" ||
                    mnemonic == "mov_hxv" ||
                    mnemonic == "mov_axr" ||
                    mnemonic == "mov_bxr" ||
                    mnemonic == "mov_cxr" ||
                    mnemonic == "mov_dxr" ||
                    mnemonic == "mov_exr" ||
                    mnemonic == "mov_fxr" ||
                    mnemonic == "mov_gxr" ||
                    mnemonic == "mov_hxr")
                    i++;

                if (i < command.size() && command[i].getValue() == ",")
                    i++;

                for (; i < command.size(); i++)
                {
                    if (command[i].getValue() != "word" && command[i].getValue() != "@")
                    {
                        if (runtime.existsVariableByName(command[i].getValue()))
                            output += runtime.getVariableByName(command[i].getValue())->getValue();
                        else
                            output += command[i].getValue();

                        if (i+1 < command.size() && command[i+1].getValue() != ",")
                            output += " ";
                    }
                }

                output += "\n";
            }
        }

        std::cout << "Writing code..." << std::endl;
        std::ofstream of(std::string(argv[1])+".out.ppt8a");
        of << output << std::endl;
        std::cout << "Compiling..." << std::endl;
        system(std::string("ppt8asm "+std::string(argv[1])+".out.ppt8a -o "+argv[3]).c_str());
        std::cout << "Finished." << std::endl << std::endl;

        if (!watch)
            return 0;
    }
}
