#include <string>
#include <iostream>
#include <regex>
#include "tokenizer.hpp"
#include "ppt8_std.hpp"

std::vector<Token> Tokenizer::tokenize(std::string code, Runtime* runtime)
{
    std::vector<Token> toks;
    std::string tmp;

    int linec = 1;
    int linei = 1;

    for (int i = 0; i < code.size(); i++)
    {
        if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n' || code[i] == ',' || code[i] == '"')
        {
            if (code[i] == '\n')
                linec++;
            tmp = "";
        }
        else if (code[i] == '#' || code[i] == ';')
        {
            while (code[i] != '\n')
                i++;
            linec++;
        }
        else if (code[i] == ':')
        {
            std::regex e("[a-zA-Z_][a-zA-Z_0-9]*");

            if (!std::regex_match(tmp, e))
            {
                std::cout << "error in line " << linec << ": invalid label name." << std::endl;
                exit(1);
            }

            if (runtime->existsNameByValue(tmp))
            {
                std::cout << "error in line " << linec << ": name \"" << tmp << "\" already exists." << std::endl;
                exit(1);
            }

            runtime->registerName(Name(tmp, NT_Label));
        }
        else
            tmp += code[i];
    }

    linec = 1;

    for (int i = 0; i < code.size(); i++)
    {
        if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n' || code[i] == ',')
        {
            if (!tmp.empty())
            {
                if (toks.size() > 0 && toks[toks.size()-1].getValue() == "alloc")
                {
                    std::regex e("[a-zA-Z_][a-zA-Z_0-9]*");
                    std::regex hex("0x[0-9a-fA-F]+");
                    std::regex bin("0b[01]+");
                    std::regex dec("0d[0-9]+");

                    if (!is_number(tmp) &&
                        !std::regex_match(tmp, hex) &&
                        !std::regex_match(tmp, bin) &&
                        !std::regex_match(tmp, dec) && tmp != "word")
                    {
                        if (!std::regex_match(tmp, e))
                        {
                            std::cout << "error in line " << linec << ": invalid alloc syntax." << std::endl;
                            exit(1);
                        }
                        else
                        {
                            if (runtime->existsNameByValue(tmp))
                            {
                                std::cout << "error in line " <<
                                    linec << ": name \"" << tmp << "\" already exists." << std::endl;
                                exit(1);
                            }

                            runtime->registerName(Name(tmp, NT_Variable));
                            toks.push_back(Token(TokenType::makeValue(tmp), TokenType("n"), linec, linei));
                        }
                    }
                    else
                    {
                        toks.push_back(Token(TokenType::makeValue(tmp),
                            TokenType::determineType(tmp, linec, runtime),
                            linec,
                            linei));
                    }
                }
                else
                {
                    toks.push_back(Token(TokenType::makeValue(tmp),
                        TokenType::determineType(tmp, linec, runtime),
                        linec,
                        linei));
                }

                tmp = "";
            }

            if (code[i] == '\n')
            {
                while (code[i] == '\n')
                {
                    i++;
                    linec++;
                }

                toks.push_back(Token("new_line", TokenType("new_line"), linec, linei));
                linei = 0;
                i--;
            }
            else if (code[i] == ',')
                toks.push_back(Token(",", TokenType(","), linec, linei));
        }
        else if (code[i] == '#' || code[i] == ';')
        {
            if (!tmp.empty())
            {
                toks.push_back(Token(TokenType::makeValue(tmp),
                    TokenType::determineType(tmp, linec, runtime),
                    linec,
                    linei));
                tmp = "";
            }

            while (i < code.size() && code[i] != '\n')
                i++;
            i--;
        }
        else if (code[i] == '@')
        {
            if (!tmp.empty())
            {
                toks.push_back(Token(TokenType::makeValue(tmp),
                    TokenType::determineType(tmp, linec, runtime),
                    linec,
                    linei));
                tmp = "";
            }

            while (code[i] == '@')
            {
                toks.push_back(Token("@", TokenType("@"), linec, linei));
                i++;
            }

            i--;
        }
        else if (code[i] == '"')
        {
            if (!tmp.empty())
            {
                toks.push_back(Token(TokenType::makeValue(tmp),
                    TokenType::determineType(tmp, linec, runtime),
                    linec,
                    linei));
                tmp = "";
            }

            i++;
            while (code[i] != '"')
            {
                if (code[i] == '\\' && code[i+1] == 'x')
                {
                    if (i+3 < code.size())
                        hexstr_to_ints(code[i+2]+std::string("")+code[i+3]);
                    else
                    {
                        std::cout << "error: line " << linec << ":" <<
                            linei << ": error with \\x in string. needs one hex byte. eg \"\\xff\"" << std::endl;
                        exit(1);
                    }

                    tmp += "\\x";
                    i++;
                }
                else if (code[i] == '\\' && code[i+1] == '\"')
                {
                    tmp += "\\x22";
                    i++;
                }
                else
                    tmp += code[i];

                i++;
            }

            toks.push_back(Token(tmp, TokenType("str"), linec, linei));
            tmp = "";
        }
        else if (code[i] == ':')
        {
            toks.push_back(Token(tmp, TokenType("label_def"), linec, linei));
            tmp = "";
        }
        else
            tmp += code[i];

        linei++;
    }

    if (!tmp.empty())
        toks.push_back(Token(TokenType::makeValue(tmp), TokenType::determineType(tmp, linec, runtime), linec, linei));

    return toks;
}

int Tokenizer::strLen(std::string str)
{
    int count = 0;

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '\\' && str[i+1] == 'x')
        {
            i += 3;
            count++;
        }
        else if (str[i] == '\\' && str[i+1] == '\"')
        {
            count++;
            i++;
        }
        else
            count++;
    }

    return count;
}