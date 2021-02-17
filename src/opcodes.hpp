#include "ram.hpp"

typedef uint16_t u16;
typedef uint8_t u8;

int NOP();
int LD_r16_u16(u8 &lower_r16, u8 &upper_r16, Ram *Ram, u16 PC);
int LD_r16_r8(u8 &lower_r16, u8 &upper_r16, u8 &r8);
int INC_r16(u8 &lower_r16, u8 &upper_r16);
int INC_r8(u8 &r8, u8 &flags);
int DEC_r8(u8 &r8, u8 &flags);
u16 JP_u16(Ram *ram, u16 PC);