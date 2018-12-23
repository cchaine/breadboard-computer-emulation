#ifndef TOOLS_H
#define TOOLS_H

#include "termcolor.hpp"
#include "ram.h"
#include <iostream>

void print_bin(unsigned char value);
void set_cursor_pos(int XPos, int YPos);
void print_module(std::string title, unsigned char value, int x1, int y1, int x2, int y2);
void print_module(std::string title, unsigned char value, int x, int y);
void print_micro_instructions(int controlWord);
void print_ram(RAM * ram);
void print_bus(unsigned char value);
void print_pc(unsigned char value);
void print_rega(unsigned char value);
void print_ram(unsigned char value);
void print_sub(unsigned char value);
void print_sum(unsigned char value);
void print_memaddr(unsigned char value);
void print_regb(unsigned char value);
void print_instr(unsigned char value);
void print_ctrlw(int controlWord);
void print_micrcntr(unsigned char value);


#endif