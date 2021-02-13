#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ram.hpp"

std::string name;

int main(int argc, char const *argv[])
{
    Ram test = Ram("cpu_instrs.gb");
    std::stringstream ssName;

    for (uint16_t i = 0x0134; i < 0x0143; i++)
    {
        ssName << (char)test.read(i);
    }

    name = ssName.str();
    std::cout << "Current Game is: " << name << "\n";
    return 0;
}