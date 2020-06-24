#ifndef COMPILER_PPT8_STD_HPP
#define COMPILER_PPT8_STD_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

bool is_number(std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

std::vector<int> decstr_to_ints(std::string s, int line, bool has_to_be16=false)
{
    if (std::stoul(s) > UINT32_MAX)
    {
        std::cout << "error in line " << line << ": number " << s << " is too big. max is uint32." << std::endl;
        exit(1);
    }

    if (is_number(s))
    {
        std::vector<int> bytes;
        unsigned long n = std::stoi(s);

        if (n > pow(2, 24))
            bytes.push_back((n >> 24) & 0xFF);

        if (n > pow(2, 16))
            bytes.push_back((n >> 16) & 0xFF);

        if (n > pow(2, 8))
            bytes.push_back((n >> 8) & 0xFF);
        else if (has_to_be16)
            bytes.push_back(0);

        bytes.push_back(n & 0xFF);
        return bytes;
    }

    return {};
}

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

std::vector<int> binstr_to_ints(std::string bin, int line)
{
    std::vector<int> ret;

    for (int i = 0; i < bin.size(); i += 8)
    {
        std::string num = bin[i]+std::string("")+bin[i+1]
                          +std::string("")+bin[i+2]
                          +std::string("")+bin[i+3]
                          +std::string("")+bin[i+4]
                          +std::string("")+bin[i+5]
                          +std::string("")+bin[i+6]
                          +std::string("")+bin[i+7];

        int x = 0;
        int c = 0;
        for (int j = num.size()-1; j >= 0; j--)
        {
            if (num[j] == '1')
                x += pow(2, c);
            else if (num[j] != '0')
            {
                std::cout << "error in line " << line << ": invalid binary number \"" << bin << "\"." << std::endl;
                exit(1);
            }

            c++;
        }

        ret.push_back(x);
    }

    return ret;
}

#endif //COMPILER_PPT8_STD_HPP
