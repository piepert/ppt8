#ifndef COMPILER_PPT8_STD_HPP
#define COMPILER_PPT8_STD_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

bool is_number(std::string s);

std::vector<int> decstr_to_ints(std::string s, int line, bool has_to_be16=false);
std::vector<int> hexstr_to_ints(std::string hex);
std::vector<int> binstr_to_ints(std::string bin, int line);

#endif //COMPILER_PPT8_STD_HPP
