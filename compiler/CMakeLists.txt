cmake_minimum_required(VERSION 3.11)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(ppt8c main.cpp tokenizer.cpp tokenizer.hpp parser.cpp parser.hpp token.cpp token.hpp token_type.cpp token_type.hpp ppt8_std.hpp name.cpp name.hpp runtime.cpp runtime.hpp ppt8_std.cpp variable.cpp variable.hpp tr.hpp)