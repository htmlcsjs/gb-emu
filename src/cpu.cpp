#include <iomanip>
#include <sstream>
#include "cpu.hpp"

Cpu::Cpu(Ram *ramPtr, Logger *loggerPointer)
{
    // Set up RAM and logging
    ram = ramPtr;
    logger = loggerPointer;
    subsystem = "CPU subsystem";

    // Registor Initisation
    
    regA = 0x00;
    regB = 0x00;
    regC = 0x00;
    regD = 0x00;
    regE = 0x00;
    regH = 0x00;
    regL = 0x00;
    flags = 0b0000000;
    SP = 0x0000;
    PC = 0x0100;


}

Cpu::~Cpu()
{
}

uint16_t Cpu::getRegister(std::string reg)
{
    if (reg == "A")
    {
        return regA;
    }
    else if (reg == "B")
    {
        return regB;
    }
    else if (reg == "C")
    {
        return regC;
    }
    else if (reg == "D")
    {
        return regD;
    }
    else if (reg == "E")
    {
        return regE;
    }
    else if (reg == "H")
    {
        return regH;
    }
    else if (reg == "L")
    {
        return regL;
    }
    else if (reg == "F")
    {
        return flags;
    }
    else if (reg == "PC")
    {
        return PC;
    }
    else if (reg == "SP")
    {
        return SP;
    }
    else
    {
        return 0;
    }
    
}

uint16_t Cpu::getPC()
{
    return PC;
}

void Cpu::loop() // Main loop function;
{

    // Temp varibles to avoid undefined behaviors
    uint8_t upper = 0x00;
    uint8_t lower = 0x00;
    
    // Main switch case for interpreting the optcode
    switch ((int)ram->read(PC))
    {
    case 0x00: // NOP
        PC++;
        break;

    case 0x01: // LD BC,u16
        regC = (int)ram->read(PC+1);
        regB = (int)ram->read(PC+2);
        PC += 3;
        break;

    case 0x02: // LD (BC),A
        regC = regA;
        PC++;
        break;

    case 0x03: // INC BC
        if (regC == 0xff)
        {
            regB++;
        }
        else
        {
            regC++;
        }      
        PC++;
        break;

    case 0x04:
        PC++;
        break;

    case 0x05:
        PC++;
        break;

    case 0x06:
        PC++;
        break;

    case 0x07:
        PC++;
        break;

    case 0x08:
        PC++;
        break;

    case 0x09:
        PC++;
        break;

    case 0x0a:
        PC++;
        break;

    case 0x0b:
        PC++;
        break;

    case 0x0c:
        PC++;
        break;

    case 0x0d:
        PC++;
        break;

    case 0x0e:
        PC++;
        break;

    case 0x0f:
        PC++;
        break;

    case 0x10:
        PC++;
        break;

    case 0x11:
        PC++;
        break;

    case 0x12:
        PC++;
        break;

    case 0x13:
        PC++;
        break;

    case 0x14:
        PC++;
        break;

    case 0x15:
        PC++;
        break;

    case 0x16:
        PC++;
        break;

    case 0x17:
        PC++;
        break;

    case 0x18:
        PC++;
        break;

    case 0x19:
        PC++;
        break;

    case 0x1a:
        PC++;
        break;

    case 0x1b:
        PC++;
        break;

    case 0x1c:
        PC++;
        break;

    case 0x1d:
        PC++;
        break;

    case 0x1e:
        PC++;
        break;

    case 0x1f:
        PC++;
        break;

    case 0x20:
        PC++;
        break;

    case 0x21:
        PC++;
        break;

    case 0x22:
        PC++;
        break;

    case 0x23:
        PC++;
        break;

    case 0x24:
        PC++;
        break;

    case 0x25:
        PC++;
        break;

    case 0x26:
        PC++;
        break;

    case 0x27:
        PC++;
        break;

    case 0x28:
        PC++;
        break;

    case 0x29:
        PC++;
        break;

    case 0x2a:
        PC++;
        break;

    case 0x2b:
        PC++;
        break;

    case 0x2c:
        PC++;
        break;

    case 0x2d:
        PC++;
        break;

    case 0x2e:
        PC++;
        break;

    case 0x2f:
        PC++;
        break;

    case 0x30:
        PC++;
        break;

    case 0x31:
        PC++;
        break;

    case 0x32:
        PC++;
        break;

    case 0x33:
        PC++;
        break;

    case 0x34:
        PC++;
        break;

    case 0x35:
        PC++;
        break;

    case 0x36:
        PC++;
        break;

    case 0x37:
        PC++;
        break;

    case 0x38:
        PC++;
        break;

    case 0x39:
        PC++;
        break;

    case 0x3a:
        PC++;
        break;

    case 0x3b:
        PC++;
        break;

    case 0x3c:
        PC++;
        break;

    case 0x3d:
        PC++;
        break;

    case 0x3e:
        PC++;
        break;

    case 0x3f:
        PC++;
        break;

    case 0x40:
        PC++;
        break;

    case 0x41:
        PC++;
        break;

    case 0x42:
        PC++;
        break;

    case 0x43:
        PC++;
        break;

    case 0x44:
        PC++;
        break;

    case 0x45:
        PC++;
        break;

    case 0x46:
        PC++;
        break;

    case 0x47:
        PC++;
        break;

    case 0x48:
        PC++;
        break;

    case 0x49:
        PC++;
        break;

    case 0x4a:
        PC++;
        break;

    case 0x4b:
        PC++;
        break;

    case 0x4c:
        PC++;
        break;

    case 0x4d:
        PC++;
        break;

    case 0x4e:
        PC++;
        break;

    case 0x4f:
        PC++;
        break;

    case 0x50:
        PC++;
        break;

    case 0x51:
        PC++;
        break;

    case 0x52:
        PC++;
        break;

    case 0x53:
        PC++;
        break;

    case 0x54:
        PC++;
        break;

    case 0x55:
        PC++;
        break;

    case 0x56:
        PC++;
        break;

    case 0x57:
        PC++;
        break;

    case 0x58:
        PC++;
        break;

    case 0x59:
        PC++;
        break;

    case 0x5a:
        PC++;
        break;

    case 0x5b:
        PC++;
        break;

    case 0x5c:
        PC++;
        break;

    case 0x5d:
        PC++;
        break;

    case 0x5e:
        PC++;
        break;

    case 0x5f:
        PC++;
        break;

    case 0x60:
        PC++;
        break;

    case 0x61:
        PC++;
        break;

    case 0x62:
        PC++;
        break;

    case 0x63:
        PC++;
        break;

    case 0x64:
        PC++;
        break;

    case 0x65:
        PC++;
        break;

    case 0x66:
        PC++;
        break;

    case 0x67:
        PC++;
        break;

    case 0x68:
        PC++;
        break;

    case 0x69:
        PC++;
        break;

    case 0x6a:
        PC++;
        break;

    case 0x6b:
        PC++;
        break;

    case 0x6c:
        PC++;
        break;

    case 0x6d:
        PC++;
        break;

    case 0x6e:
        PC++;
        break;

    case 0x6f:
        PC++;
        break;

    case 0x70:
        PC++;
        break;

    case 0x71:
        PC++;
        break;

    case 0x72:
        PC++;
        break;

    case 0x73:
        PC++;
        break;

    case 0x74:
        PC++;
        break;

    case 0x75:
        PC++;
        break;

    case 0x76:
        PC++;
        break;

    case 0x77:
        PC++;
        break;

    case 0x78:
        PC++;
        break;

    case 0x79:
        PC++;
        break;

    case 0x7a:
        PC++;
        break;

    case 0x7b:
        PC++;
        break;

    case 0x7c:
        PC++;
        break;

    case 0x7d:
        PC++;
        break;

    case 0x7e:
        PC++;
        break;

    case 0x7f:
        PC++;
        break;

    case 0x80:
        PC++;
        break;

    case 0x81:
        PC++;
        break;

    case 0x82:
        PC++;
        break;

    case 0x83:
        PC++;
        break;

    case 0x84:
        PC++;
        break;

    case 0x85:
        PC++;
        break;

    case 0x86:
        PC++;
        break;

    case 0x87:
        PC++;
        break;

    case 0x88:
        PC++;
        break;

    case 0x89:
        PC++;
        break;

    case 0x8a:
        PC++;
        break;

    case 0x8b:
        PC++;
        break;

    case 0x8c:
        PC++;
        break;

    case 0x8d:
        PC++;
        break;

    case 0x8e:
        PC++;
        break;

    case 0x8f:
        PC++;
        break;

    case 0x90:
        PC++;
        break;

    case 0x91:
        PC++;
        break;

    case 0x92:
        PC++;
        break;

    case 0x93:
        PC++;
        break;

    case 0x94:
        PC++;
        break;

    case 0x95:
        PC++;
        break;

    case 0x96:
        PC++;
        break;

    case 0x97:
        PC++;
        break;

    case 0x98:
        PC++;
        break;

    case 0x99:
        PC++;
        break;

    case 0x9a:
        PC++;
        break;

    case 0x9b:
        PC++;
        break;

    case 0x9c:
        PC++;
        break;

    case 0x9d:
        PC++;
        break;

    case 0x9e:
        PC++;
        break;

    case 0x9f:
        PC++;
        break;

    case 0xa0:
        PC++;
        break;

    case 0xa1:
        PC++;
        break;

    case 0xa2:
        PC++;
        break;

    case 0xa3:
        PC++;
        break;

    case 0xa4:
        PC++;
        break;

    case 0xa5:
        PC++;
        break;

    case 0xa6:
        PC++;
        break;

    case 0xa7:
        PC++;
        break;

    case 0xa8:
        PC++;
        break;

    case 0xa9:
        PC++;
        break;

    case 0xaa:
        PC++;
        break;

    case 0xab:
        PC++;
        break;

    case 0xac:
        PC++;
        break;

    case 0xad:
        PC++;
        break;

    case 0xae:
        PC++;
        break;

    case 0xaf:
        PC++;
        break;

    case 0xb0:
        PC++;
        break;

    case 0xb1:
        PC++;
        break;

    case 0xb2:
        PC++;
        break;

    case 0xb3:
        PC++;
        break;

    case 0xb4:
        PC++;
        break;

    case 0xb5:
        PC++;
        break;

    case 0xb6:
        PC++;
        break;

    case 0xb7:
        PC++;
        break;

    case 0xb8:
        PC++;
        break;

    case 0xb9:
        PC++;
        break;

    case 0xba:
        PC++;
        break;

    case 0xbb:
        PC++;
        break;

    case 0xbc:
        PC++;
        break;

    case 0xbd:
        PC++;
        break;

    case 0xbe:
        PC++;
        break;

    case 0xbf:
        PC++;
        break;

    case 0xc0:
        PC++;
        break;

    case 0xc1:
        PC++;
        break;

    case 0xc2:
        PC++;
        break;

    case 0xc3: // JP u16
        upper = (int)ram->read(PC + 2);
        lower = (int)ram->read(PC + 1);
        PC = lower + (upper * 0x100);
        logger->log(0, subsystem, "Jumping to: " + intToHexString(lower + (upper * 0x100)));
        break;

    case 0xc4:
        PC++;
        break;

    case 0xc5:
        PC++;
        break;

    case 0xc6:
        PC++;
        break;

    case 0xc7:
        PC++;
        break;

    case 0xc8:
        PC++;
        break;

    case 0xc9:
        PC++;
        break;

    case 0xca:
        PC++;
        break;

    case 0xcb:
        PC++;
        break;

    case 0xcc:
        PC++;
        break;

    case 0xcd:
        PC++;
        break;

    case 0xce:
        PC++;
        break;

    case 0xcf:
        PC++;
        break;

    case 0xd0:
        PC++;
        break;

    case 0xd1:
        PC++;
        break;

    case 0xd2:
        PC++;
        break;

    case 0xd3:
        PC++;
        break;

    case 0xd4:
        PC++;
        break;

    case 0xd5:
        PC++;
        break;

    case 0xd6:
        PC++;
        break;

    case 0xd7:
        PC++;
        break;

    case 0xd8:
        PC++;
        break;

    case 0xd9:
        PC++;
        break;

    case 0xda:
        PC++;
        break;

    case 0xdb:
        PC++;
        break;

    case 0xdc:
        PC++;
        break;

    case 0xdd:
        PC++;
        break;

    case 0xde:
        PC++;
        break;

    case 0xdf:
        PC++;
        break;

    case 0xe0:
        PC++;
        break;

    case 0xe1:
        PC++;
        break;

    case 0xe2:
        PC++;
        break;

    case 0xe3:
        PC++;
        break;

    case 0xe4:
        PC++;
        break;

    case 0xe5:
        PC++;
        break;

    case 0xe6:
        PC++;
        break;

    case 0xe7:
        PC++;
        break;

    case 0xe8:
        PC++;
        break;

    case 0xe9:
        PC++;
        break;

    case 0xea:
        PC++;
        break;

    case 0xeb:
        PC++;
        break;

    case 0xec:
        PC++;
        break;

    case 0xed:
        PC++;
        break;

    case 0xee:
        PC++;
        break;

    case 0xef:
        PC++;
        break;

    case 0xf0:
        PC++;
        break;

    case 0xf1:
        PC++;
        break;

    case 0xf2:
        PC++;
        break;

    case 0xf3:
        PC++;
        break;

    case 0xf4:
        PC++;
        break;

    case 0xf5:
        PC++;
        break;

    case 0xf6:
        PC++;
        break;

    case 0xf7:
        PC++;
        break;

    case 0xf8:
        PC++;
        break;

    case 0xf9:
        PC++;
        break;

    case 0xfa:
        PC++;
        break;

    case 0xfb:
        PC++;
        break;

    case 0xfc:
        PC++;
        break;

    case 0xfd:
        PC++;
        break;

    case 0xfe:
        PC++;
        break;

    case 0xff:
        PC++;
        break;

    default:
        break;
    }
    logger->log(0, subsystem, "PC: " + intToHexString(PC));
}