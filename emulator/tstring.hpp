#include <utility>

#ifndef TSTRING_LIBRARY_HPP
#define TSTRING_LIBRARY_HPP

#include <sstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <stdio.h>

namespace tri
{
    class string
    {
    private:
        std::string str;

        static inline std::string &ltrim(std::string &s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            std::not1(std::ptr_fun<int, int>(std::isspace))));
            return s;
        }

        static inline std::string &rtrim(std::string &s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }

        std::string trimf()
        {
            return ltrim(rtrim(str));
        }

        std::vector<std::string> splitf(char delim)
        {
            std::vector<std::string> elems;
            std::string tmp;

            for (char c : str)
            {
                if (c == delim)
                {
                    elems.push_back(tmp);
                    tmp = "";
                }
                else tmp += c;
            }

            elems.push_back(tmp);
            return elems;
        }

        bool replace(std::string& str, const std::string& from, const std::string& to)
        {
            size_t start_pos = str.find(from);
            if(start_pos == std::string::npos)
                return false;

            str.replace(start_pos, from.length(), to);
            return true;
        }

    public:
        string(const std::string &s) : str(s) {}
        string() { str=""; }
        string(const char *c) : str(c) {}
        string(const char r) : str(std::string(1, r)) {}

        bool find(const string &s)
        {
            return str.find(s.cxs()) != std::string::npos;
        }

        bool equals(const tri::string &s)
        {
            string s1 = str;
            return s1.cxs().compare(s.cxs()) != 0;
        }

        bool equalsIgnoreCase(tri::string s)
        {
            return toLower() == s.toLower();
        }

        inline bool empty() const
        {
            return str.empty();
        }

        const std::string &cxs() const
        {
            return str;
        }

        const char* cs()
        {
            return str.c_str();
        }

        tri::string trim()
        {
            return tri::string(trimf());
        }

        tri::string reverse()
        {
            std::string s = str;
            std::reverse(s.begin(), s.end());

            return tri::string(s);
        }

        std::vector<string> split(const char &delim)
        {
            std::vector<string> tstrs;
            for (auto &s : splitf(delim))
                tstrs.emplace_back(tri::string(s));
            return tstrs;
        }

        std::vector<string> split(const std::string &delim=" ")
        {
            std::vector<string> tstrs;
            std::string s = str;

            size_t pos = 0;
            std::string token;

            while ((pos = s.find(delim)) != std::string::npos)
            {
                token = s.substr(0, pos);
                tstrs.push_back(tri::string(token));
                s.erase(0, pos + delim.length());
            }

            tstrs.push_back(tri::string(s));
            return tstrs;
        }

        char at(const int &index)
        {
            return str[index];
        }

        long long size() const
        {
            return str.size();
        }

        tri::string operator+(const tri::string &s)
        {
            return tri::string(str += s.str);
        }

        tri::string operator+(const std::string &s)
        {
            return tri::string(str += s);
        }

        tri::string operator+(const char* s)
        {
            return tri::string(str += s);
        }

        tri::string operator=(const tri::string &s)
        {
            return tri::string(str = s.str);
        }

        tri::string operator=(const std::string &s)
        {
            return tri::string(str = s);
        }

        tri::string operator=(const char* s)
        {
            return tri::string(str = s);
        }

        tri::string operator=(const char c)
        {
            return tri::string(str = c);
        }

        tri::string operator+=(const tri::string &s)
        {
            return tri::string(str += s.str);
        }

        tri::string operator+=(const std::string &s)
        {
            return tri::string(str += s);
        }

        tri::string operator+=(const char* s)
        {
            return tri::string(str += s);
        }

        bool operator==(const char* s)
        {
            return (cxs() == s);
        }

        bool operator==(const std::string &s)
        {
            return (cxs() == s);
        }

        bool operator==(const tri::string &s)
        {
            return (str == s.cxs());
        }

        bool operator!=(const char* s)
        {
            return (cxs() != s);
        }

        bool operator!=(const std::string &s)
        {
            return (cxs() != s);
        }

        bool operator!=(const tri::string &s)
        {
            return (str != s.cxs());
        }

        friend std::ostream &operator<<(std::ostream &os, const tri::string &s)
        {
            os << s.cxs();
            return os;
        }

        tri::string toUpper()
        {
            std::string tmp;

            for (char c : str)
            {
                tmp += (char) std::toupper(c);
            }

            return string(tmp);
        }

        tri::string toLower()
        {
            std::string tmp;

            for (char c : str)
            {
                tmp += (char) std::tolower(c);
            }

            return string(tmp);
        }

        tri::string replace(const char* from, const char* to)
        {
            return replace(std::string(from), std::string(to));
        }

        tri::string replace(const tri::string &from, const tri::string &to)
        {
            for (int i = 0; i < str.size(); i++)
                replace(str, from.cxs(), to.cxs());
            return tri::string(str);
        }

        tri::string replace(const std::string &from, const std::string &to)
        {
            for (int i = 0; i < str.size(); i++)
                replace(str, from, to);
            return tri::string(str);
        }

        std::vector<char> toCharArray()
        {
            return (std::vector<char>(str.begin(), str.end()));
        }

        bool endsWith(const tri::string &s)
        {
            return string(str.substr(str.size() - s.size(), str.size())).cxs() == s.cxs();
        }

        bool startsWith(const tri::string &s)
        {
            return string(str.substr(0, s.size())).cxs() == s.cxs();
        }

        string substr(unsigned long start, unsigned long end)
        {
            return str.substr(start, end);
        }
    };
}

#endif
