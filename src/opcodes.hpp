#pragma once

#include "ram.hpp"
#include "logging.hpp" 


int NOP();
int LD_r16_u16(u8 &lower_r16, u8 &upper_r16, Ram *Ram, u16 PC);
int LD_mem_r16_r8(u8 &lower_r16, u8 &upper_r16, u8 &r8, Ram *ram);
int INC_r16(u8 &lower_r16, u8 &upper_r16);
int INC_r8(u8 &r8, u8 &flags);
int DEC_r8(u8 &r8, u8 &flags);
int LD_r8_u8(u8 &r8, Ram *ram, u16 PC);
int RLCA(u8 &r8, u8 &flags);
u16 JP_u16(Ram *ram, u16 PC);