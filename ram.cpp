#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ram.hpp"

Ram::Ram(std::string romLocation)
{
    sections = "SECTIONS OF GAMEBOY RAM:\n"
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
}

std::string Ram::info()
{
    return sections;
}

std::byte Ram::read(uint16_t address)
{
    // read a std::byte at `address`
    std::byte data{0xff};
    return data;
}

void Ram::write(uint16_t address, std::byte data)
{
    // write to valid place in ram
}


Ram::~Ram()
{
    // Deconstuct here
}

