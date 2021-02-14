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
    uint16_t AF;
    uint16_t BC;
    uint16_t DE;
    uint16_t HL;
    uint16_t SP;
    uint16_t PC;
    
public:
    Cpu(Ram* ramPtr, Logger * loggerPtr);
    ~Cpu();
    void loop(); // function to call in the main loop
    uint16_t getPC();
};


