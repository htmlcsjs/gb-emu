cmake_minimum_required(VERSION 3.0)
project("gb-emu")
include_directories(./src/)
set(CMAKE_CXX_FLAGS  "-g -Wall -static -std=c++17")

add_executable(gb-emu.out main.cpp
    ./src/cpu.cpp
    ./src/logging.cpp
    ./src/ram.cpp
)