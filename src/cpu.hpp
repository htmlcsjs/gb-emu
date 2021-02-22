#pragma once

#include "opcodes.hpp"
#include "ram.hpp"
#include "logging.hpp"
#include "utils.cpp"

class Cpu
{
private:
    // Pointers to other subsystems
    Logger* logger;
    Ram* ram;
    
    // Subsystem Info
    std::string subsystem;

    // CPU Registors
    u8 regA;
    u8 regB;
    u8 regC;
    u8 regD;
    u8 regE;
    u8 regH;
    u8 regL;
    u8 flags;
    u16 PC;
    u16 SP;

public:

    Cpu(Ram* ramPtr, Logger * loggerPtr);
    ~Cpu();
    void loop(); // function to call in the main loop
    u16 getPC();
    u16 getRegister(std::string reg);
};
