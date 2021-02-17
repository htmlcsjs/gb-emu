#include "opcodes.hpp"

u8 flagZ = 0b10000000;
u8 flagN = 0b01000000;
u8 flagH = 0b00100000;
u8 flagC = 0b00010000;
typedef uint8_t u8;
typedef uint16_t u16;

    int
    NOP()
{
    return 1;
}

int LD_r16_u16(u8 &lower_r16, u8 &upper_r16, Ram *ram, u16 PC)
{
    lower_r16 = (int)ram->read(PC + 1);
    upper_r16 = (int)ram->read(PC + 2);
    return 3;
}

int LD_r16_r8(u8 &lower_r16, u8 &upper_r16, u8 &r8)
{
    r8 = lower_r16;
    return 1;
}

int INC_r16(u8 &lower_r16, u8 &upper_r16)
{
    if (lower_r16 == 0xff)
    {
        upper_r16++;
        lower_r16++;
    }
    else
    {
        lower_r16++;
    }
    return 1;
}

int INC_r8(u8 &r8, u8 &flags)
{
    r8++;
    flags &= ~flagN;
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

int DEC_r8(u8 &r8, u8 &flags)
{
    r8--;
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

u16 JP_u16(Ram *ram, u16 PC)
{
    u8 upper = (int)ram->read(PC + 2);
    u8 lower = (int)ram->read(PC + 1);
    u16 returnVal = lower + (upper * 0x100);
    return returnVal;
}
