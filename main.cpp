#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "cpu.hpp"

std::string name;

int main(int argc, char const *argv[])
{
    // Init the subsystems
    Logger logger = Logger("gb-emu", false, 0);
    Ram ram = Ram("cpu_instrs.gb", &logger);
    Cpu cpu = Cpu(&ram, &logger);

    // Read the name of the game from the cartrige
    std::stringstream ssName;
    for (uint16_t i = 0x0134; i < 0x0143; i++)
    {
        ssName << (char)ram.read(i);
    }
    name = ssName.str();
    logger.log(1, "Main", "Current Game is: "+ name);

    while (cpu.getPC() < 0xffff)
    {
        cpu.loop();
    }
    

    return 0;
}