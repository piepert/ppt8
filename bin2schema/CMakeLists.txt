cmake_minimum_required(VERSION 3.16)
project(bin2schema)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(ppt8b2s
        main.cpp)