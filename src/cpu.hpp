#include "ram.hpp"

class Cpu
{
private:
    // Pointers to other subsystems
    Logger* logger;
    Ram* ram;
    
    // Subsystem Info
    std::string subsystem;

    // CPU Registors
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t regD;
    uint8_t regE;
    uint8_t regH;
    uint8_t regL;
    uint8_t flags;
    uint16_t PC;
    uint16_t SP;

    // Flag locations
    uint8_t flagZ;
    uint8_t flagN;
    uint8_t flagH;
    uint8_t flagC;

public:
    Cpu(Ram* ramPtr, Logger * loggerPtr);
    ~Cpu();
    void loop(); // function to call in the main loop
    uint16_t getPC();
    uint16_t getRegister(std::string reg);
};


