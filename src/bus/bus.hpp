#pragma once

#include "../ram.hpp"

namespace emulator 
{
    namespace bus
    {
        namespace cartridge
        {
            // 0x0000 - 0x7fff
            std::vector<u8[0x3fff]> romBanks;
            int currentBank = 1;
            
            u8 read(u16 address);
            void setRegisters(u16 address, u8 data);
            void setup(std::string filename);
        }
        namespace VRAM
        {
            // 0x8000 - 0x9fff
            u8[0x1fff] RAM;
            u8 read(u16 address);
            void write(u16 address, u8 data);
        }
        namespace BBRAM
        {
            // 0x000 - 0x9fff
            u8[0x1fff] RAM;
            u8 read(u16 address);
            void write(u16 address, u8 data);
            void save(std::string address);
        }
        namespace WRAM
        {
            // 0xc000 - 0xdfff, Will have to add bank swapping for CGB
            u8[0x1fff] RAM;
            u8 read(u16 address);
            void write(u16 address, u8 data);
        }
        // ECHO RAM (done in meta functions)
        namespace OAM
        {
            // 0xfe00-0xfe9f TODO WITH GPU
        }
        // NOT IN USE
        namespace registers
        {
            // 0xff00-0xff7f
            u8[0x7f] regs;
            u8 read(u16 reg);
            void write(u16 reg, u8 data);
        }
        namespace HRAM
        {
            // 0xff80 - 0xfffe
            u8[0x7e] RAM;
            u8 read(u16 address);
            void write(u16 address, u8 data);
        }
        namespace IEReg
        {
            // 0xffff
            u8 reg;
            u8 read();
            void write(u8 data);
        }
        u8 metaRead(u16 address);
        void metaWrite(u16 address, u8 data);
    }
}