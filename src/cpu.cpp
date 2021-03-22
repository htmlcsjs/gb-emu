#include <iomanip>
#include <sstream>
#include "cpu.hpp"

emulator::Cpu::Cpu(Ram *ramPtr, Logger *loggerPointer)
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
    flags = 0x0;
    SP = 0x0000;
    PC = 0x0100;

    // Flag constants
    flagZ = 0b10000000;
    flagN = 0b01000000;
    flagH = 0b00100000;
    flagC = 0b00010000;
}

emulator::Cpu::~Cpu()
{
}

uint16_t emulator::Cpu::getRegister(std::string reg)
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

uint16_t emulator::Cpu::getPC()
{
    return PC;
}

void emulator::Cpu::loop() // Main loop function;
{
    using namespace emulator;

    // Main switch case for interpreting the opcode
    switch ((int)ram->read(PC))
    {
    case 0x00: // NOP
        PC += opcodes::NOP();
        break;

    case 0x01: // LD BC,u16
        PC += opcodes::LD_r16_u16(regC, regB, ram, PC);
        break;

    case 0x02: // LD (BC),A
        PC += opcodes::LD_mem_r16_r8(regC, regB, regA, ram);
        break;

    case 0x03: // INC BC
        PC += opcodes::INC_r16(regC, regB);
        break;

    case 0x04: // INC B
        PC += opcodes::INC_r8(regB, flags);
        break;

    case 0x05: // DEC B
        PC += opcodes::DEC_r8(regB, flags);
        break;

    case 0x06: // LD B,u8
        PC += opcodes::LD_r8_u8(regB, ram, PC);
        break;

    case 0x07: // RLCA
        PC += opcodes::RLCA(regA, flags);
        break;

    case 0x08: // LD u16, SP
        PC += opcodes::LD_u16_SP(SP, ram, PC);
        break;

    case 0x09: // ADD HL,BC
        PC += opcodes::ADD_HL_r16(regC, regB, regH, regL, flags);
        break;

    case 0x0a: // LD A,(BC)
        PC += opcodes::LD_r8_mem_r16(regC, regB, regA, ram);
        break;

    case 0x0b: // DEC BC
        PC += opcodes::DEC_r16(regC, regB);
        break;

    case 0x0c: // INC C
        PC += opcodes::INC_r8(regC, flags);
        break;

    case 0x0d: // DEC C
        PC += opcodes::DEC_r8(regC, flags);
        break;

    case 0x0e: // LD C,u8
        PC += opcodes::LD_r8_u8(regC, ram, PC);
        break;

    case 0x0f: // RRCA
        PC += opcodes::RRCA(regA, flags);
        break;

    case 0x10: // STOP
        PC += opcodes::STOP(ram);
        break;

    case 0x11: // LD DE,u16
        PC += opcodes::LD_r16_u16(regE, regD, ram, PC);
        break;

    case 0x12: // LD (DE),A
        PC += opcodes::LD_mem_r16_r8(regE, regD, regA, ram);
        break;

    case 0x13: // INC DE
        PC += opcodes::INC_r16(regE, regD);
        break;

    case 0x14: // INC D
        PC += opcodes::INC_r8(regD, flags);
        break;

    case 0x15: // DEC D
        PC += opcodes::DEC_r8(regD, flags);
        break;

    case 0x16: // LD D,u8
        PC += opcodes::LD_r8_u8(regD, ram, PC);
        break;

    case 0x17: // RLA
        PC += opcodes::RLA(regA, flags);
        break;

    case 0x18: // JR e8
        PC = opcodes::JR_cc_e8(ram, PC, true);
        break;

    case 0x19: // ADD HL,DE
        PC += opcodes::ADD_HL_r16(regE, regD, regH, regL, flags);
        break;

    case 0x1a: // LD A,(DE)
        PC += opcodes::LD_r8_mem_r16(regE, regD, regA, ram);
        break;

    case 0x1b: // DEC DE
        PC += opcodes::DEC_r16(regE, regD);
        break;

    case 0x1c: // INC E
        PC += opcodes::INC_r8(regE, flags);
        break;

    case 0x1d: // DEC E
        PC += opcodes::DEC_r8(regE, flags);
        break;

    case 0x1e: // LD E,u8
        PC += opcodes::LD_r8_u8(regE, ram, PC);
        break;

    case 0x1f: // RRA
        PC += opcodes::RRA(regA, flags);
        break;

    case 0x20: // JR NZ,e8
        PC = opcodes::JR_cc_e8(ram, PC, ((flags & flagZ) == 0));
        break;

    case 0x21: // LD HL,u16
        PC += opcodes::LD_r16_u16(regL, regH, ram, PC);
        break;

    case 0x22: // LD (HL+),A
        opcodes::INC_r16(regL, regH);
        PC += opcodes::LD_mem_r16_r8(regL, regH, regA, ram);
        opcodes::DEC_r16(regL, regH);
        break;

    case 0x23: // INC HL
        PC += opcodes::INC_r16(regL, regH);
        break;

    case 0x24: // INC H
        PC += opcodes::INC_r8(regH, flags);
        break;

    case 0x25: // DEC H
        PC += opcodes::DEC_r8(regH, flags);
        break;

    case 0x26: // LD H,u8
        PC += opcodes::LD_r8_u8(regH, ram, PC);
        break;

    case 0x27: // TODO DAA
        PC += 1;
        break;

    case 0x28: // JR Z,e8
        PC = PC = opcodes::JR_cc_e8(ram, PC, ((flags & flagZ) == flagZ));
        break;

    case 0x29: // ADD HL,HL
        PC += opcodes::ADD_HL_r16(regL, regH, regH, regL, flags);
        break;

    case 0x2a: // LD A,(HL+)
        opcodes::INC_r16(regL, regH);
        PC += opcodes::LD_r8_mem_r16(regL, regH, regA, ram);
        opcodes::DEC_r16(regL, regH);
        break;

    case 0x2b: // DEC HL
        PC += opcodes::DEC_r16(regL, regH);
        break;

    case 0x2c: // INC L
        PC += opcodes::INC_r8(regL, flags);
        break;

    case 0x2d: // DEC L
        PC += opcodes::DEC_r8(regL, flags);
        break;

    case 0x2e: // LD L,u8
        PC += opcodes::LD_r8_u8(regL, ram, PC);
        break;

    case 0x2f:
        PC += 1;
        break;

    case 0x30:
        PC += 1;
        break;

    case 0x31:
        PC += 1;
        break;

    case 0x32:
        PC += 1;
        break;

    case 0x33:
        PC += 1;
        break;

    case 0x34:
        PC += 1;
        break;

    case 0x35:
        PC += 1;
        break;

    case 0x36:
        PC += 1;
        break;

    case 0x37:
        PC += 1;
        break;

    case 0x38:
        PC += 1;
        break;

    case 0x39:
        PC += 1;
        break;

    case 0x3a:
        PC += 1;
        break;

    case 0x3b:
        PC += 1;
        break;

    case 0x3c:
        PC += 1;
        break;

    case 0x3d:
        PC += 1;
        break;

    case 0x3e:
        PC += 1;
        break;

    case 0x3f:
        PC += 1;
        break;

    case 0x40:
        PC += 1;
        break;

    case 0x41:
        PC += 1;
        break;

    case 0x42:
        PC += 1;
        break;

    case 0x43:
        PC += 1;
        break;

    case 0x44:
        PC += 1;
        break;

    case 0x45:
        PC += 1;
        break;

    case 0x46:
        PC += 1;
        break;

    case 0x47:
        PC += 1;
        break;

    case 0x48:
        PC += 1;
        break;

    case 0x49:
        PC += 1;
        break;

    case 0x4a:
        PC += 1;
        break;

    case 0x4b:
        PC += 1;
        break;

    case 0x4c:
        PC += 1;
        break;

    case 0x4d:
        PC += 1;
        break;

    case 0x4e:
        PC += 1;
        break;

    case 0x4f:
        PC += 1;
        break;

    case 0x50:
        PC += 1;
        break;

    case 0x51:
        PC += 1;
        break;

    case 0x52:
        PC += 1;
        break;

    case 0x53:
        PC += 1;
        break;

    case 0x54:
        PC += 1;
        break;

    case 0x55:
        PC += 1;
        break;

    case 0x56:
        PC += 1;
        break;

    case 0x57:
        PC += 1;
        break;

    case 0x58:
        PC += 1;
        break;

    case 0x59:
        PC += 1;
        break;

    case 0x5a:
        PC += 1;
        break;

    case 0x5b:
        PC += 1;
        break;

    case 0x5c:
        PC += 1;
        break;

    case 0x5d:
        PC += 1;
        break;

    case 0x5e:
        PC += 1;
        break;

    case 0x5f:
        PC += 1;
        break;

    case 0x60:
        PC += 1;
        break;

    case 0x61:
        PC += 1;
        break;

    case 0x62:
        PC += 1;
        break;

    case 0x63:
        PC += 1;
        break;

    case 0x64:
        PC += 1;
        break;

    case 0x65:
        PC += 1;
        break;

    case 0x66:
        PC += 1;
        break;

    case 0x67:
        PC += 1;
        break;

    case 0x68:
        PC += 1;
        break;

    case 0x69:
        PC += 1;
        break;

    case 0x6a:
        PC += 1;
        break;

    case 0x6b:
        PC += 1;
        break;

    case 0x6c:
        PC += 1;
        break;

    case 0x6d:
        PC += 1;
        break;

    case 0x6e:
        PC += 1;
        break;

    case 0x6f:
        PC += 1;
        break;

    case 0x70:
        PC += 1;
        break;

    case 0x71:
        PC += 1;
        break;

    case 0x72:
        PC += 1;
        break;

    case 0x73:
        PC += 1;
        break;

    case 0x74:
        PC += 1;
        break;

    case 0x75:
        PC += 1;
        break;

    case 0x76:
        PC += 1;
        break;

    case 0x77:
        PC += 1;
        break;

    case 0x78:
        PC += 1;
        break;

    case 0x79:
        PC += 1;
        break;

    case 0x7a:
        PC += 1;
        break;

    case 0x7b:
        PC += 1;
        break;

    case 0x7c:
        PC += 1;
        break;

    case 0x7d:
        PC += 1;
        break;

    case 0x7e:
        PC += 1;
        break;

    case 0x7f:
        PC += 1;
        break;

    case 0x80:
        PC += 1;
        break;

    case 0x81:
        PC += 1;
        break;

    case 0x82:
        PC += 1;
        break;

    case 0x83:
        PC += 1;
        break;

    case 0x84:
        PC += 1;
        break;

    case 0x85:
        PC += 1;
        break;

    case 0x86:
        PC += 1;
        break;

    case 0x87:
        PC += 1;
        break;

    case 0x88:
        PC += 1;
        break;

    case 0x89:
        PC += 1;
        break;

    case 0x8a:
        PC += 1;
        break;

    case 0x8b:
        PC += 1;
        break;

    case 0x8c:
        PC += 1;
        break;

    case 0x8d:
        PC += 1;
        break;

    case 0x8e:
        PC += 1;
        break;

    case 0x8f:
        PC += 1;
        break;

    case 0x90:
        PC += 1;
        break;

    case 0x91:
        PC += 1;
        break;

    case 0x92:
        PC += 1;
        break;

    case 0x93:
        PC += 1;
        break;

    case 0x94:
        PC += 1;
        break;

    case 0x95:
        PC += 1;
        break;

    case 0x96:
        PC += 1;
        break;

    case 0x97:
        PC += 1;
        break;

    case 0x98:
        PC += 1;
        break;

    case 0x99:
        PC += 1;
        break;

    case 0x9a:
        PC += 1;
        break;

    case 0x9b:
        PC += 1;
        break;

    case 0x9c:
        PC += 1;
        break;

    case 0x9d:
        PC += 1;
        break;

    case 0x9e:
        PC += 1;
        break;

    case 0x9f:
        PC += 1;
        break;

    case 0xa0:
        PC += 1;
        break;

    case 0xa1:
        PC += 1;
        break;

    case 0xa2:
        PC += 1;
        break;

    case 0xa3:
        PC += 1;
        break;

    case 0xa4:
        PC += 1;
        break;

    case 0xa5:
        PC += 1;
        break;

    case 0xa6:
        PC += 1;
        break;

    case 0xa7:
        PC += 1;
        break;

    case 0xa8:
        PC += 1;
        break;

    case 0xa9:
        PC += 1;
        break;

    case 0xaa:
        PC += 1;
        break;

    case 0xab:
        PC += 1;
        break;

    case 0xac:
        PC += 1;
        break;

    case 0xad:
        PC += 1;
        break;

    case 0xae:
        PC += 1;
        break;

    case 0xaf:
        PC += 1;
        break;

    case 0xb0:
        PC += 1;
        break;

    case 0xb1:
        PC += 1;
        break;

    case 0xb2:
        PC += 1;
        break;

    case 0xb3:
        PC += 1;
        break;

    case 0xb4:
        PC += 1;
        break;

    case 0xb5:
        PC += 1;
        break;

    case 0xb6:
        PC += 1;
        break;

    case 0xb7:
        PC += 1;
        break;

    case 0xb8:
        PC += 1;
        break;

    case 0xb9:
        PC += 1;
        break;

    case 0xba:
        PC += 1;
        break;

    case 0xbb:
        PC += 1;
        break;

    case 0xbc:
        PC += 1;
        break;

    case 0xbd:
        PC += 1;
        break;

    case 0xbe:
        PC += 1;
        break;

    case 0xbf:
        PC += 1;
        break;

    case 0xc0:
        PC += 1;
        break;

    case 0xc1:
        PC += 1;
        break;

    case 0xc2:
        PC += 1;
        break;

    case 0xc3: // JP u16
        PC = opcodes::JP_u16(ram, PC);
        logger->log(0, subsystem, "Jumping to: " + intToHexString(PC));
        break;

    case 0xc4:
        PC += 1;
        break;

    case 0xc5:
        PC += 1;
        break;

    case 0xc6:
        PC += 1;
        break;

    case 0xc7:
        PC += 1;
        break;

    case 0xc8:
        PC += 1;
        break;

    case 0xc9:
        PC += 1;
        break;

    case 0xca:
        PC += 1;
        break;

    case 0xcb:
        PC += 1;
        break;

    case 0xcc:
        PC += 1;
        break;

    case 0xcd:
        PC += 1;
        break;

    case 0xce:
        PC += 1;
        break;

    case 0xcf:
        PC += 1;
        break;

    case 0xd0:
        PC += 1;
        break;

    case 0xd1:
        PC += 1;
        break;

    case 0xd2:
        PC += 1;
        break;

    case 0xd3:
        PC += 1;
        break;

    case 0xd4:
        PC += 1;
        break;

    case 0xd5:
        PC += 1;
        break;

    case 0xd6:
        PC += 1;
        break;

    case 0xd7:
        PC += 1;
        break;

    case 0xd8:
        PC += 1;
        break;

    case 0xd9:
        PC += 1;
        break;

    case 0xda:
        PC += 1;
        break;

    case 0xdb:
        PC += 1;
        break;

    case 0xdc:
        PC += 1;
        break;

    case 0xdd:
        PC += 1;
        break;

    case 0xde:
        PC += 1;
        break;

    case 0xdf:
        PC += 1;
        break;

    case 0xe0:
        PC += 1;
        break;

    case 0xe1:
        PC += 1;
        break;

    case 0xe2:
        PC += 1;
        break;

    case 0xe3:
        PC += 1;
        break;

    case 0xe4:
        PC += 1;
        break;

    case 0xe5:
        PC += 1;
        break;

    case 0xe6:
        PC += 1;
        break;

    case 0xe7:
        PC += 1;
        break;

    case 0xe8:
        PC += 1;
        break;

    case 0xe9:
        PC += 1;
        break;

    case 0xea:
        PC += 1;
        break;

    case 0xeb:
        PC += 1;
        break;

    case 0xec:
        PC += 1;
        break;

    case 0xed:
        PC += 1;
        break;

    case 0xee:
        PC += 1;
        break;

    case 0xef:
        PC += 1;
        break;

    case 0xf0:
        PC += 1;
        break;

    case 0xf1:
        PC += 1;
        break;

    case 0xf2:
        PC += 1;
        break;

    case 0xf3:
        PC += 1;
        break;

    case 0xf4:
        PC += 1;
        break;

    case 0xf5:
        PC += 1;
        break;

    case 0xf6:
        PC += 1;
        break;

    case 0xf7:
        PC += 1;
        break;

    case 0xf8:
        PC += 1;
        break;

    case 0xf9:
        PC += 1;
        break;

    case 0xfa:
        PC += 1;
        break;

    case 0xfb:
        PC += 1;
        break;

    case 0xfc:
        PC += 1;
        break;

    case 0xfd:
        PC += 1;
        break;

    case 0xfe:
        PC += 1;
        break;

    case 0xff:
        PC += 1;
        break;

    default:
        break;
    }
    logger->log(0, subsystem, "PC: " + intToHexString(PC));
}