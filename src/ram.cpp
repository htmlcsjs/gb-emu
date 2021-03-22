#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "ram.hpp"

emulator::Ram::Ram(std::string romLocation, Logger *loggerPtr)
{
    // Sections of the 16-but address bus
    sections = "SECTIONS OF GAMEBUY ADDRESS BUS:\n"
               "0x0000-0x3FFF: 16KB ROM bank 00    - loaded from ROM, normally static\n"
               "0x4000-0x7FFF: 16KB ROM bank 01-NN - loaded from ROM, should be swichable, though not implemented right now\n"
               "0x8000-0x9FFF: 8KB  VRAM\n"
               "0xA000-0xBFFF: 8KB  Cartrige Ram\n"
               "0xC000-0xCFFF: 4kb  WRAM bank 0\n"
               "0xD000-0xDFFF: 4kb  WRAM bank 1-n\n"
               "0xE000-0xFDFF: ECHO RAM            - echos 0xC000-0xDDFF\n"
               "0xFE00-0xFE9F: OAM                 - Sprite attribute table\n"
               "0xFEA0-0xFEFF: Unusable\n"
               "0xFF00-0xFF7F: I/O Registers\n"
               "0xFF80-0xFFFE: High Ram\n"
               "0xFFFF-0xFFFF: Interrupts Enable Register (IE)";
    abbreviations = "r8 - Any of the 8-bit registers (A, B, C, D, E, H, L).\n"
                    "r16 - Any of the general-purpose 16-bit registers (BC, DE, HL).\n"
                    "u8  - 8-bit integer constant.\n"
                    "u16 - 16-bit integer constant.\n"
                    "e8  - 8-bit offset (-128 to 127).\n"
                    "u3  - 3-bit unsigned integer constant (0 to 7).\n";
    // Init logger
    logger = loggerPtr;
    subsystem = "RAM subsystem";

    // Initalise the whole bus with 0x00
    for (size_t i = 0; i < 0xffff; i++)
    {
        storage.push_back((std::byte) 0x00);
    }
    std::string msg = "RAM size is: " + std::to_string(storage.size()) + " bytes";
    logger->log(1, subsystem, msg);

    // Open the ROM file so we can read the size from it.
    std::ifstream sizeRom(romLocation, std::ios::binary | std::ios::ate);
    long length = sizeRom.tellg()-1;
    sizeRom.close();

    // If the ROM is too thicc for the address bus, cancel execution
    if (length != 0x7fff)
    {
        logger->log(4, subsystem, "The ROM file provided is not 32KiB in size");
        throw std::overflow_error("The Rom file provided is not 32kib in size");
    } 
    else
    {
        // load rom file for Reading
        std::ifstream rom(romLocation, std::ios::binary);
        
        // Read a 0x7fff portion from the ROM file 
        char * buffer = new char[0x7fff];
        rom.read(buffer, 0x7fff);

        // loop every byte in buffer and append to storage vector 
        for (u16 i = 0; i < 0x7fff; i++)
        {
            std::byte data{(unsigned char)buffer[i]};
            storage[i] = data;
        }
        logger->log(1, subsystem, "ROM copied to RAM");
        // Clean up memory
        delete buffer;
        rom.close();
    }   
}

std::string emulator::Ram::info(std::string type)
{
    if (type == "sections")
    {
        return sections;
    }
    else if (type == "abbr")
    {
        return abbreviations;
    }   
}

std::byte emulator::Ram::read(u16 address)
{
    // read a std::byte at `address`
    if (address <= 0xE000 && address >= 0xfdff)
    {
        return storage[address-0x2000];
    }
    else if (address <= 0xfea0 && address >= 0xfeff)
    {
        return (std::byte)0x00;
        logger->log(2, subsystem, "Something tried to acsess a invalid place in memory");
    }
    
    return storage[address];
}

void emulator::Ram::write(u16 address, std::byte data)
{
    // print serial data to the console
    if (address == 0xFF02 && data == (std::byte)0x81)
    {
        std::string charStr(1, (char)read(0xff01));
        std::cout << charStr;
    }
    storage[address] = data;
}


emulator::Ram::~Ram()
{
    // Deconstuct here
}


