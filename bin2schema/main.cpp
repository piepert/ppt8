#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

#define CARD_SIZE 30

bool is_int(const std::string& s, int base){
   if(s.empty() || std::isspace(s[0])) return false ;
   char * p ;
   strtol(s.c_str(), &p, base) ;
   return (*p == 0) ;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

// std::vector<char> count_table = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v' };
std::vector<std::string> count_table = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "X", "Y", "Z", "1", "2", "3", "4", "5", "6" };

std::string generate_file(const std::string &templ_file, std::string &templ_table, std::vector<std::vector<std::string>> holes)
{
    std::string file_contents = templ_file;
    std::string table_copy;
    std::string tables;

    for (int i = 0; i < 5; i++)
    {
        std::vector<std::string> hs;

        for (int j = 0; j < 8; j++)
            hs.push_back("◯");

        holes.insert(holes.begin(), hs);
    }

    while (holes.size() % 30 != 0)
    {
        std::vector<std::string> hs;

        for (int j = 0; j < 8; j++)
            hs.push_back("◯");

        holes.push_back(hs);
    }

    for (int i = 0; i < holes.size(); i++)
    {
        std::vector<std::string>* hole = &holes[i];

        if (i % CARD_SIZE == 0 && i != CARD_SIZE)
        {
            std::cout << i << " | CARD " << i / CARD_SIZE + (i == 0 ? 1 : 0) << " / PAGE " << (int) ((float) ((i) / CARD_SIZE) / 2 + 0.5f) + (i == 0 ? 1 : 0) << std::endl;
            tables += table_copy;
            table_copy = templ_table;
            replace(table_copy, ":t>XX", ":t>["+std::to_string(i/CARD_SIZE + (i == 0 ? 1 : 0))+"]");
        }

        for (int j = 0; j < hole->size(); j++)
        {
            std::string name = std::string(count_table[i % CARD_SIZE + (i == CARD_SIZE ? CARD_SIZE*0 : 0)]) + std::to_string(j+1);
            std::string h = hole->operator[](j);

            while (table_copy.find(":t>"+name) != std::string::npos)
                replace(table_copy, ":t>"+name, ":t>"+h);
            // std::cout << i << " | " << name << " -> " << h << std::endl;
        }
    }

    tables += table_copy;
    replace(file_contents, "{{TABLE}}", tables);
    return file_contents;
}

std::vector<std::string> num_to_hole(unsigned int n)
{
    std::vector<std::string> str;

    for(int i = 0; n > 0; i++)
    {
        if (n % 2 == 0) {
            str.push_back("◯");
        } else {
            str.push_back("⬤");
        }

        n = n / 2;
    }

    while (str.size() < 8)
        str.push_back("◯");

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
    bool output_file = false;
    std::string ofilename;

    if (argc == 2) {

    } else if (argc != 3 && argc != 4) {
        std::cout << "(e1) wrong syntax. use \"ppt8bs <file> [<index>|c|-o <filename>]\"" << std::endl;
        return 1;

    } else if (argc == 3 || argc == 4) {
        word = argv[2];

        if (!is_int(word, 10)) {
            if (word != "c" && word != "-o") {
                std::cout << "(e2) wrong syntax. use \"ppt8bs <file> [<index>|c|-o <filename>]\"" << std::endl;
                return 1;
            } else if (word == "-o") {
                if (argc != 4) {
                    std::cout << "(e3) wrong syntax. use \"ppt8bs <file> [<index>|c|-o <filename>]\"" << std::endl;
                    return 1;
                }

                ofilename = argv[3];
                output_file = true;
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
    std::vector<std::vector<std::string>> holes;

    // off: ◯ || on: ●

    while (!feof(fp))
    {
        c = fgetc(fp);                            // get a character/byte from the file
        if (feof(fp))
            continue;

        holes.push_back(num_to_hole(c));

        if (output_file)
            continue;

        if (index != -1 && count == index)
        {
            std::cout << index << " >>  1  2  3  4  5  |  6  7  8" << std::endl;
            std::cout << index << " (c" << (count % CARD_SIZE != 0 && count % CARD_SIZE < 10 ? "0" : "") << (count % CARD_SIZE == 0 ? CARD_SIZE : count % CARD_SIZE) << ")" <<  " >>  " << holes_to_str(num_to_hole(c)) << std::endl;
            return 0;
        }
        else if (index == -1)
        {
            // printf("Read from file %02x\n\r",c);    // and show it in hex format
            // std::cout << "CHAR: " << std::hex << (int) c << std::dec << std::endl;

            if (word == "c") {
                std::cout << std::setw(7) << count << "      " << " >>  1  2  3  4  5  |  6  7  8" << std::endl;
            }

            std::cout << std::setw(7) << count << " (c" << (count % CARD_SIZE != 0 && count % CARD_SIZE < 10 ? "0" : "") << (count % CARD_SIZE == 0 ? CARD_SIZE : count % CARD_SIZE) << ")" << " >>  " << holes_to_str(num_to_hole(c)) << std::endl << std::endl;

            if (word == "c") {
                std::cin.get();
                std::cout << std::endl;
            }

            if (count % CARD_SIZE == 0)
            {
                cc++;
                std::cout << "NEW CARD (" << cc << " / page " << (int) ((float) (cc % CARD_SIZE) / 2 + 0.5) << ")" << std::endl << std::endl;

                std::cin.sync();
                std::cin.get();
            }

            spaces = "";
        }

        count += 1;
    }

    if (output_file)
    {
        std::ifstream ifs_file("paper_template.xml");
        std::string templ_file((std::istreambuf_iterator<char>(ifs_file)),
                        std::istreambuf_iterator<char>());

        std::ifstream ifs_table("table_template.xml");
        std::string templ_table((std::istreambuf_iterator<char>(ifs_table)),
                        std::istreambuf_iterator<char>());

        std::ofstream ofs(ofilename);

        ofs << generate_file(templ_file, templ_table, holes);
    }

    fclose(fp);
    return 0;
}