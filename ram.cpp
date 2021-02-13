#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "ram.hpp"

Ram::Ram(std::string romLocation)
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

    // Initalise the whole bus with 0x00
    for (size_t i = 0; i < 0xffff; i++)
    {
        storage.push_back((std::byte) 0x00);
    }
    std::cout << "Ram size is: " << storage.size() << " bytes\n";

    // Open the ROM file so we can read the size from it.
    std::ifstream romForSize(romLocation, std::ios::binary | std::ios::ate);
    long length = romForSize.tellg()-1;
    romForSize.close();

    // If the ROM is too thicc for the address bus, cancel execution
    if (length != 0x7fff)
    {
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
        for (uint16_t i = 0; i < 0x7fff; i++)
        {
            std::byte data{(unsigned char)buffer[i]};
            storage[i] = data;          
            //std::cout << "data varible copyed to storage position " << i << "\n";
        }

        // Clean up memory
        delete buffer;
        rom.close();
    }   
}

std::string Ram::info()
{
    return sections;
}

std::byte Ram::read(uint16_t address)
{
    // read a std::byte at `address`
    return storage[address];
}

void Ram::write(uint16_t address, std::byte data)
{
    // print to the console corrospnding to the GPU
    if (address == 0xFF02 && data == (std::byte)0x81)
    {
        std::cout << (int)read(0xFF01);
    }
    storage[address] = data;
}


Ram::~Ram()
{
    // Deconstuct here
}


