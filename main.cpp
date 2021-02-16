#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "cpu.hpp"

std::string name;

int main(int argc, char const *argv[])
{
    // Init the subsystems
    Logger logger = Logger("gb-emu", false, 1);
    Ram ram = Ram(argv[1], &logger);
    Cpu cpu = Cpu(&ram, &logger);

    // Read the name of the game from the cartrige
    std::stringstream ssName;
    for (uint16_t i = 0x0134; i < 0x013E; i++)
    {
        ssName << (char)ram.read(i);
    }
    name = ssName.str();
    logger.log(1, "Main", "Current Game is: "+ name);

    // main loop
    while (cpu.getPC() < 0x7fff)
    {
        cpu.loop();
    }
    
    // Log the state of the Registors after execution
    logger.log(1, "Main", "Registors are:");
    logger.log(1, "Main", "A: " + intToHexString(cpu.getRegister("A")));
    logger.log(1, "Main", "B: " + intToHexString(cpu.getRegister("B")));
    logger.log(1, "Main", "C: " + intToHexString(cpu.getRegister("C")));
    logger.log(1, "Main", "D: " + intToHexString(cpu.getRegister("D")));
    logger.log(1, "Main", "E: " + intToHexString(cpu.getRegister("E")));
    logger.log(1, "Main", "H: " + intToHexString(cpu.getRegister("H")));
    logger.log(1, "Main", "L: " + intToHexString(cpu.getRegister("L")));
    logger.log(1, "Main", "The stack pointer is: " + intToHexString(cpu.getRegister("SP")));
    logger.log(1, "Main", "The flags are: " + intToBinString(cpu.getRegister("F")));

    return 0;
}