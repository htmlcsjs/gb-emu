#include "opcodes.hpp"

u8 flagZ = 0b10000000;
u8 flagN = 0b01000000;
u8 flagH = 0b00100000;
u8 flagC = 0b00010000;
typedef uint8_t u8;
typedef uint16_t u16;

using namespace emulator;

int opcodes::NOP()
{
    return 1;
}

int opcodes::LD_r16_u16(u8 &lower_r16, u8 &upper_r16, Ram *ram, u16 PC)
{
    lower_r16 = (int)ram->read(PC + 1);
    upper_r16 = (int)ram->read(PC + 2);
    return 3;
}

int opcodes::LD_mem_r16_r8(u8 &lower_r16, u8 &upper_r16, u8 &r8, Ram *ram)
{
    u16 address = lower_r16 + (upper_r16 * 0x100);
    std::byte data{r8};
    ram->write(address, data);
    return 1;
}

int opcodes::INC_r16(u8 &lower_r16, u8 &upper_r16)
{
    u16 r16 = (upper_r16 << 8) | lower_r16;
    r16++;
    lower_r16 = r16 & 0xff;
    upper_r16 = r16 >> 8;
    return 1;
}

int opcodes::INC_r8(u8 &r8, u8 &flags)
{
    r8++;
    flags &= ~(flagH + flagN + flagZ);

    if (r8 == 0)
    {
        flags |= flagZ;
    }
    if ((r8 & 0xf) == 0x0)
    {
        flags |= flagH;
    }
    return 1;
}

int opcodes::DEC_r8(u8 &r8, u8 &flags)
{
    r8--;
    flags &= ~(flagH + flagN + flagZ);
    flags |= flagN;
    if (r8 == 0x0)
    {
        flags |= flagZ;
    }
    if ((r8 & 0xf) == 0xf)
    {
        flags |= flagH;
    }
    return 1;
}

int opcodes::LD_r8_u8(u8 &r8, Ram *ram, u16 PC)
{
    u8 data = (int)ram->read(PC+1);
    r8 = data;
    return 2;
}

int opcodes::RLCA(u8 &r8, u8& flags)
{
    u8 bit0;
    if ((r8 & 0x80) == 0x80)
    {
        flags = flagC;
        bit0 = 1;
    }
    else
    {
        flags = 0;
    }
    r8 = r8 << 1;
    r8 += bit0;
    return 1;
}

int opcodes::LD_u16_SP(u16 &SP, Ram *ram, u16 PC)
{
    u16 address = (int)ram->read(PC + 1) + ((int)ram->read(PC + 2) * 0x100);
    std::byte dataLow{SP & 0xff};
    std::byte dataHigh{SP >> 8};
    ram->write(address, dataLow);
    ram->write(address+1, dataHigh);
    return 3;
}

int opcodes::ADD_HL_r16(u8 &lower_r16, u8 &upper_r16, u8 &regH, u8 &regL, u8 &flags)
{
    u16 r16 = (upper_r16 << 8) | lower_r16;
    u16 HL = (regH << 8) | regL;
    
    u32 result = HL + r16;
    flags &= ~(flagH + flagN + flagC);
    HL = result & 0xffff;

    lower_r16 = r16 & 0xff;
    upper_r16 = r16 >> 8;
    regL = HL & 0xff;
    regH = HL >> 8;

    if ((HL & 0xfff + r16 & 0xfff) > 0xfff)
    {
        flags |= flagH;
    }
    if (result > 0xffff)
    {
        flags |= flagC;
    }
    
    return 1;
}

int opcodes::LD_r8_mem_r16(u8 &lower_r16, u8 &upper_r16, u8 &r8, Ram *ram)
{
    u16 address = lower_r16 + (upper_r16 * 0x100);
    r8 = (u8)ram->read(address);
    return 1;
}

int opcodes::DEC_r16(u8 &lower_r16, u8 &upper_r16)
{
    u16 r16 = (upper_r16 << 8) | lower_r16;
    r16--;
    lower_r16 = r16 & 0xff;
    upper_r16 = r16 >> 8;
    return 1;
}

int opcodes::RRCA(u8 &r8, u8 &flags)
{
    u8 bit7;
    if ((r8 & 0x1) == 0x1)
    {
        flags = flagC;
        bit7 = 0x80;
    }
    else
    {
        flags = 0;
    }
    r8 = r8 >> 1;
    r8 += bit7;
    return 1;
}

int opcodes::STOP(Ram *ram)
{
    // TODO: Impliment stopping when i do input and impliment GBC mode swiching
    // Currently acts as 2 wide NOP
    return 2;
}

int opcodes::RLA(u8 &r8, u8 &flags)
{
    if ((r8 & 0x80) == 0x80)
    {
        flags = flagC;
    }
    else
    {
        flags = 0;
    }
    r8 = r8 << 1;
    return 1;
}

u16 opcodes::JR_e8(Ram *ram, u16 PC)
{
    u16 jmpAddress = PC + (int)ram->read(PC+1);
    return jmpAddress;
}

int opcodes::RRA(u8 &r8, u8 &flags)
{
    if ((r8 & 0x1) == 0x1)
    {
        flags = flagC;
    }
    else
    {
        flags = 0;
    }
    r8 = r8 >> 1;
    return 1;
}

u16 opcodes::JP_u16(Ram *ram, u16 PC)
{
    u8 upper = (int)ram->read(PC + 2);
    u8 lower = (int)ram->read(PC + 1);
    u16 returnVal = lower + (upper * 0x100);
    return returnVal;
}
