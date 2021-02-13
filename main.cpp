#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ram.hpp"

std::string name;

int main(int argc, char const *argv[])
{
    Logger logger = Logger("gb-emu", false, 0);
    Ram test = Ram("cpu_instrs.gb", false, 0);
    std::stringstream ssName;

    for (uint16_t i = 0x0134; i < 0x0143; i++)
    {
        ssName << (char)test.read(i);
    }

    name = ssName.str();
    logger.log(1, "Main", "Current Game is: "+ name);
    return 0;
}