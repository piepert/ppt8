#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

bool is_int(const std::string& s, int base){
   if(s.empty() || std::isspace(s[0])) return false ;
   char * p ;
   strtol(s.c_str(), &p, base) ;
   return (*p == 0) ;
}


std::vector<std::string> num_to_hole(unsigned int n)
{
    std::vector<std::string> str;

    for(int i = 0; n > 0; i++)
    {
        if (n % 2 == 0) {
            str.push_back("⚪");
        } else {
            str.push_back("⚫");
        }

        n = n / 2;
    }

    while (str.size() < 8)
        str.push_back("⚪");

    return str;
}

std::string holes_to_str(std::vector<std::string> s)
{
    std::string ret;

    for (int i = 0; i < s.size(); i++)
    {
        if (i == 5)
            ret += " |  ";
        ret += s[i] + " ";
    }

    return ret;
}

int main(int argc, char* argv[]) {
    std::string word = "";
    long index = -1;

    if (argc == 2) {

    } else if (argc != 3) {
        std::cout << "(e1) wrong syntax. use \"bin2schema <file> [<index>|c]\"" << std::endl;
        return 1;

    } else if (argc == 3) {
        word = argv[2];

        if (!is_int(word, 10)) {
            if (word != "c") {
                std::cout << "(e2) wrong syntax. use \"bin2schema <file> [<index>|c]\"" << std::endl;
                return 1;
            }
        } else {
            index = std::stoi(word);
        }
    }

    std::cout << "# 2 = " << holes_to_str(num_to_hole(2)) << std::endl << std::endl << std::endl;

    std::string spaces = "";
    int count = 1;
    int cc = 1;

    for (int i = 0; i < 5; i++)
    {
        count++;
    }

    if (index != -1)
        index += 5;

    unsigned char c;                            // a single byte buffer
    FILE *fp = fopen(argv[1], "r");             // open the file in 'read' mode

    while (!feof(fp))
    {
        c = fgetc(fp);                            // get a character/byte from the file

        if (index != -1 && count == index)
        {
            std::cout << index << " >>  1  2  3  4  5  |  6  7  8" << std::endl;
            std::cout << index << " (c" << (count % 31 != 0 && count % 31 < 10 ? "0" : "") << (count % 31 == 0 ? 31 : count % 31) << ")" <<  " >>  " << holes_to_str(num_to_hole(c)) << std::endl;
            return 0;
        }
        else if (index == -1)
        {
            // printf("Read from file %02x\n\r",c);    // and show it in hex format
            // std::cout << "CHAR: " << std::hex << (int) c << std::dec << std::endl;

            if (word == "c") {
                std::cout << std::setw(7) << count << "      " << " >>  1  2  3  4  5  |  6  7  8" << std::endl;
            }

            std::cout << std::setw(7) << count << " (c" << (count % 31 != 0 && count % 31 < 10 ? "0" : "") << (count % 31 == 0 ? 31 : count % 31) << ")" << " >>  " << holes_to_str(num_to_hole(c)) << std::endl << std::endl;

            if (word == "c") {
                std::cin.get();
                std::cout << std::endl;
            }

            if (count % 31 == 0)
            {
                cc++;
                std::cout << "NEW CARD (" << cc << " / page " << (int) ((float) (cc % 31) / 2 + 0.5) << ")" << std::endl << std::endl;

                std::cin.sync();
                std::cin.get();
            }

            spaces = "";
        }

        count += 1;
    }

    fclose(fp);
    return 0;
}