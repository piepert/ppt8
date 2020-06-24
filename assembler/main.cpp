#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <cstring>

#include <cmath>
#include <vector>
#include <regex>

uint16_t combine_8bit_to_16bit(uint8_t high, uint8_t low)
{
    return (high << 8) | (low & 0xff);
}

uint8_t get_higher_8bit_from_16bit(uint16_t val)
{
    return (val >> 8) & 0xff;
}

uint8_t get_lower_8bit_from_16bit(uint16_t val)
{
    return val & 0xff;
}

std::map<std::string, int> TRANSLATION = {
    { "mov_rr", 1 },
    { "mov_rv", 2 },
    { "mov_mr", 3 },
    { "mov_ss", 4 },
    { "mov_ms", 5 },
    { "mov_sv", 6 },
    { "mov_mv", 7 },
    { "mov_mm", 8 },
    { "mov_imv", 9 },
    { "mov_irm", 10 },
    { "mov_rm", 11 },
    { "mov_imr", 12 },
    { "mov_sm", 13 },
    { "mov_irs", 14 },
    { "call", 15 },
    { "mov_axv", 16 },
    { "mov_bxv", 17 },
    { "mov_cxv", 18 },
    { "mov_dxv", 19 },
    { "mov_exv", 20 },
    { "mov_fxv", 21 },
    { "mov_gxv", 22 },
    { "mov_hxv", 23 },
    { "mov_axr", 24 },
    { "mov_bxr", 25 },
    { "mov_cxr", 26 },
    { "mov_dxr", 27 },
    { "mov_exr", 28 },
    { "mov_fxr", 29 },
    { "mov_gxr", 30 },
    { "mov_hxr", 31 },
    { "alloc", 32 },
    { "int_v", 33 },
    { "int_r", 34 },
    { "int_s", 35 },
    { "int_m", 36 },
    { "push8_s", 37 },
    { "push8_m", 38 },
    { "push8_v", 39 },
    { "push16_r", 40 },
    { "push16_m", 41 },
    { "push16_v", 42 },
    { "pop8_s", 43 },
    { "pop8_m", 44 },
    { "pop16_r", 45 },
    { "pop16_m", 46 },
    { "ret", 47 },
    { "add_rr", 48 },
    { "add_rv", 49 },
    { "add_rm", 50 },
    { "add_mr", 51 },
    { "add_mv", 52 },
    { "add_rs", 53 },
    { "add_ms", 54 },
    { "add_sv", 55 },
    { "sub_rr", 56 },
    { "sub_rv", 57 },
    { "sub_rm", 58 },
    { "sub_mr", 59 },
    { "sub_mv", 60 },
    { "sub_rs", 61 },
    { "sub_ms", 62 },
    { "sub_sv", 63 },
    { "mul_rr", 64 },
    { "mul_rv", 65 },
    { "mul_rm", 66 },
    { "mul_mr", 67 },
    { "mul_mv", 68 },
    { "mul_rs", 69 },
    { "mul_ms", 70 },
    { "mul_sv", 71 },
    { "div_rr", 72 },
    { "div_rv", 73 },
    { "div_rm", 74 },
    { "div_mr", 75 },
    { "div_mv", 76 },
    { "div_rs", 77 },
    { "div_ms", 78 },
    { "div_sv", 79 },
    { "inc8_s", 80 },
    { "inc8_m", 81 },
    { "inc16_r", 82 },
    { "inc16_m", 83 },
    { "dec8_s", 84 },
    { "dec8_m", 85 },
    { "dec16_r", 86 },
    { "dec16_m", 87 },
    { "cmp_rm", 88 },
    { "cmp_sm", 89 },
    { "cmp_mv", 90 },
    { "cmp_sv", 91 },
    { "cmp_rv", 92 },
    { "jmp_v", 93 },
    { "jmp_r", 94 },
    { "jmp_m", 95 },
    { "je_v", 96 },
    { "je_r", 97 },
    { "je_m", 98 },
    { "jl_v", 99 },
    { "jl_r", 100 },
    { "jl_m", 101 },
    { "jg_v", 102 },
    { "jg_r", 103 },
    { "jg_m", 104 },
    { "jn_v", 105 },
    { "jn_r", 106 },
    { "jn_m", 107 },
    { "and_rr", 108 },
    { "and_ss", 109 },
    { "and_rv", 110 },
    { "and_sv", 111 },
    { "or_rr", 112 },
    { "or_ss", 113 },
    { "or_rv", 114 },
    { "or_sv", 115 },
    { "not_r", 116 },
    { "not_s", 117 },
    { "nand_rr", 120 },
    { "nand_ss", 121 },
    { "nand_rv", 122 },
    { "nand_sv", 123 },
    { "nor_rr", 124 },
    { "nor_ss", 125 },
    { "nor_rv", 126 },
    { "nor_sv", 127 },
    { "xor_rr", 128 },
    { "xor_ss", 129 },
    { "xor_rv", 130 },
    { "xor_sv", 131 },
    { "mov_irr", 132 },
    { "mov_irv", 133 },
    { "mov_rir", 134 },
    { "mov_sir", 135 },
    { "mov_mir", 136 },
    { "add_ss", 137 },
    { "sub_ss", 138 },
    { "mul_ss", 139 },
    { "div_ss", 140 },
    { "mov_axm", 141 },
    { "mov_bxm", 142 },
    { "mov_cxm", 143 },
    { "mov_dxm", 144 },
    { "mov_exm", 145 },
    { "mov_fxm", 146 },
    { "mov_gxm", 147 },
    { "mov_hxm", 148 },
    { "cmp_mm", 149 },
    { "cmp_rr", 150 },
    { "cmp_ss", 151 },

    { "ax", 1 },
    { "bx", 2 },
    { "cx", 3 },
    { "dx", 4 },
    { "ex", 5 },
    { "fx", 6 },
    { "gx", 7 },
    { "hx", 8 },

    { "ah", 1 },
    { "bh", 2 },
    { "ch", 3 },
    { "dh", 4 },
    { "eh", 5 },
    { "fh", 6 },
    { "gh", 7 },
    { "hh", 8 },

    { "al", 9 },
    { "bl", 10 },
    { "cl", 11 },
    { "dl", 12 },
    { "el", 13 },
    { "fl", 14 },
    { "gl", 15 },
    { "hl", 16 }
};

struct t_token {
    bool is_num = false;
    bool is_label = false;
    uint8_t num_val = 0;
    std::string code;
    int line;
};

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

std::map<std::string, int> labels;

std::vector<t_token> lex(std::string code)
{
    std::vector<t_token> ret;
    std::string tmp;
    int line_c = 1;

    for (int i = 0; i < code.size(); i++)
    {
        if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n' || code[i] == ',' || code[i] == ';')
        {
            if (code[i] == '\n')
                line_c++;

            t_token t;
            t.line = line_c;
            t.is_num = is_number(tmp);
            t.code = tmp;

            if (is_number(tmp))
            {
                for (auto i : decstr_to_ints(tmp, line_c))
                {
                    t.num_val = i;
                    ret.push_back(t);
                }
            }
            else
            {
                if (tmp != "")
                    ret.push_back(t);
            }

            if (code[i] == ',' || code[i] == ';')
            {
                t.code = code[i];
                t.is_num = false;
                t.num_val = 0;
                ret.push_back(t);
            }

            tmp = "";
        }
        else if (code[i] == '\"')
        {
            i++;
            t_token t;
            int bl = line_c;

            while (i < code.size() && code[i] != '\"')
            {
                if (code[i] == '\n')
                    line_c++;

                if (code[i] == '\\' && code[i+1] == 'x')
                {
                    i += 2;
                    int x = 0;

                    std::string s = code[i]+std::string("")+code[i+1];
                    sscanf(s.c_str(), "%x", &x);

                    t.is_num = true;
                    t.num_val = x;
                    t.line = line_c;
                    ret.push_back(t);

                    i += 2;
                    continue;
                }

                t.is_num = true;

                if (i+1 < code.size())
                {
                    if (code[i]+std::string("")+code[i+1] == "Ä")
                        t.num_val = 0xC4;

                    else if (code[i]+std::string("")+code[i+1] == "Ö")
                        t.num_val = 0xD6;

                    else if (code[i]+std::string("")+code[i+1] == "Ü")
                        t.num_val = 0xDC;

                    else if (code[i]+std::string("")+code[i+1] == "ä")
                        t.num_val = 0xE4;

                    else if (code[i]+std::string("")+code[i+1] == "ö")
                        t.num_val = 0xF6;

                    else if (code[i]+std::string("")+code[i+1] == "ü")
                        t.num_val = 0xFC;

                    else if (code[i]+std::string("")+code[i+1] == "ß")
                        t.num_val = 0xDF;
                    else
                    {
                        t.num_val = code[i];
                        i--;
                    }

                    i++;
                }
                else
                    t.num_val = code[i];

                ret.push_back(t);
                i++;
            }

            if (i >= code.size())
            {
                std::cout << "error at line " << bl << ": missing ending \"!" << std::endl;
                exit(1);
            }

            continue;
        }
        else if (code[i] == ':')
        {
            std::regex e("[a-zA-Z_][a-zA-Z_0-9]*");

            if (!std::regex_match(tmp, e))
            {
                std::cout << "error in line " << line_c << ": invalid label name." << std::endl;
                exit(1);
            }

            labels.insert(std::make_pair(tmp, -1));

            t_token t;
            t.is_label = true;
            t.is_num = false;
            t.code = tmp;
            t.line = line_c;
            t.num_val = -1;
            ret.push_back(t);

            tmp = "";
        }
        else if (code[i] == '0' && (code[i+1] == 'x' || code[i+1] == 'd' || code[i+1] == 'b'))
        {
            i++;
            std::string type;
            type = code[i];

            i++;
            std::string num;
            int x = 0;

            while (code[i] != ' ' && code[i] != '\t' && code[i] != '\n' && code[i] != ',' && code[i] != ';' && i < code.size())
            {
                if (code[i] == '\n')
                    line_c++;

                num.push_back(code[i]);
                i++;
            }

            if (code[i] == '\n')
                line_c++;

            if (type == "x")
            {
                if (num.size() % 2 != 0)
                {
                    std::cout << "error in line " << line_c << ": hex number has to have an even length." << std::endl;
                    exit(1);
                }

                x = -1;
                t_token t;
                t.is_num = true;

                for (auto i : hexstr_to_ints(num))
                {
                    t.num_val = i;
                    t.line = line_c;
                    ret.push_back(t);
                }
            }
            else if (type == "d")
            {
                try
                {
                    x = std::stoi(num);

                    if (x > 255)
                    {
                        std::cout << "error in line " << line_c << ": decimal number is too big. max size is 255." << std::endl;
                        exit(1);
                    }
                }
                catch(const std::exception& e)
                {
                    std::cout << "error in line " << line_c << ": invalid decimal number." << std::endl;
                }
            }
            else if (type == "b")
            {
                if (num.size() % 8 != 0)
                {
                    std::cout << "error in line " << line_c << ": bin number has to have the length of a multiple of 8. " << std::endl;
                    exit(1);
                }

                x = -1;
                t_token t;
                t.is_num = true;

                for (auto i : binstr_to_ints(num, line_c))
                {
                    t.num_val = i;
                    t.line = line_c;
                    ret.push_back(t);
                }
            }

            if (x == -1)
                continue;

            t_token t;
            t.is_num = true;
            t.num_val = x;
            t.line = line_c;
            ret.push_back(t);
            continue;
        }
        else
            tmp.push_back(code[i]);
    }

    t_token t;
    t.is_num = is_number(tmp);
    t.code = tmp;
    t.line = line_c;

    if (is_number(tmp))
    {
        for (auto i : decstr_to_ints(tmp, line_c))
        {
            t.num_val = i;
            ret.push_back(t);
        }
    }
    else
    {
        if (tmp != "")
            ret.push_back(t);
    }

    return ret;
}

bool map_contains(std::map<std::string, int> &map, std::string key)
{
    auto it = map.find(key);

    if (it != map.end())
        return true;
    return false;
}

std::vector<uint8_t> compile(std::vector<t_token> tokens)
{
    std::vector<uint8_t> ret;
    int index = 0;

    for (auto t : tokens)
    {
        if (t.is_label)
        {
            labels[t.code] = ret.size();
            continue;
        }

        if (t.code == "," || t.code == ";")
            continue;

        if (t.is_num)
            ret.push_back(t.num_val);
        else
        {
            if (!map_contains(TRANSLATION, t.code))
            {
                if (!map_contains(labels, t.code))
                {
                    std::cout << "error in line " << t.line << ": name \"" << t.code << "\" not found." << std::endl;
                    exit(1);
                }
                else
                {
                    ret.push_back(0);
                    ret.push_back(0);
                }

            }
            else
                ret.push_back(TRANSLATION[t.code]);

        }

        index += 1;
    }

    ret.clear();
    for (auto t : tokens)
    {
        if (t.is_label)
            continue;

        if (t.code == "," || t.code == ";")
            continue;

        if (t.is_num)
        {
            ret.push_back(t.num_val);
            // std::cout << "PUSH0: " << std::hex << (int) t.num_val << std::dec << std::endl;
        }
        else
        {
            if (!map_contains(TRANSLATION, t.code))
            {
                // std::cout << t.code << std::endl;
                std::vector<int> v = decstr_to_ints(std::to_string(labels[t.code]), t.line, true);

                ret.push_back(v[0]);
                ret.push_back(v[1]);
                // std::cout << "PUSH1: " << std::hex << v[0] << std::dec << std::endl;
                // std::cout << "PUSH2: " << std::hex << v[1] << std::dec << std::endl;
            }
            else
            {
                ret.push_back(TRANSLATION[t.code]);
                // std::cout << "PUSH3: " << std::hex << (int) TRANSLATION[t.code] << std::dec << std::endl;
            }

        }
    }

    return ret;
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "error: wrong syntax." << std::endl;
        std::cout << "syntax: ppt8asm <sourcefile> -o <outputfile>" << std::endl;
        return 1;
    }

    if (std::string(argv[2]) != "-o")
    {
        std::cout << "error: wrong syntax: \"" << argv[2] << "\"" << std::endl;
        std::cout << "syntax: ppt8asm <sourcefile> -o <outputfile>" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);

    if (!ifs.is_open())
    {
        std::cout << "error: file not found." << std::endl;
        return 1;
    }

    std::string str((std::istreambuf_iterator<char>(ifs)),
                    std::istreambuf_iterator<char>());
    std::ofstream ofs(argv[3]);

    for (char c : compile(lex(str)))
        ofs << c;

    return 0;
}