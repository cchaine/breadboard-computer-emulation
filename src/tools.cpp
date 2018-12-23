#include "tools.h"

std::string controls[] = { "CE", "CO", "CI", "AI", "AO", "SO", "SUB", "BI", "BO", "IO", "II", "MI", "RO", "RI", "HLT" }; 

void print_bin(unsigned char value) {
  for(int i = 0; i < 8; i++) {
    if((value & (1 << (7 - i))) != 0) {
      std::cout << termcolor::green << "1" << termcolor::reset;
    } else {
      std::cout << termcolor::grey << "0" << termcolor::reset;
    }
  }
}

void set_cursor_pos(int XPos, int YPos)
{
  printf("\033[%d;%dH", YPos+1, XPos+1);
}

void print_module(std::string title, unsigned char value, int x1, int y1, int x2, int y2) {
    set_cursor_pos(x1, y1);
    std::cout << "[" + title + "] ";
    set_cursor_pos(x2, y2);
    print_bin(value);
}

void print_module(std::string title, unsigned char value, int x, int y) {
    print_module(title, value, x, y, x, y+1);
}

void print_micro_instructions(int controlWord) {
    std::cout << std::endl;
    printf("\033[%d;%dH", 16, 15);
    for(int i = 0; i < sizeof(controls)/24; i++) {
        if((controlWord & (1 << (sizeof(controls)/24 - i - 1)))  == (1 << (sizeof(controls)/24 - 1 - i))) {
            std::cout << termcolor::green;            
        } else {
            std::cout << termcolor::grey;
        }
        std::cout << controls[i] << " ";
    }
    std::cout << termcolor::reset << std::endl;
}

void print_ram(RAM * ram) {
    set_cursor_pos(4, 0);
    std::cout << "[RAM] ";
    for(int i = 0; i < ram->getSize(); i++) {
        set_cursor_pos(0, i+1);
        std::cout << termcolor::white << "0x" << std::hex << i << " ";
        print_bin(ram->get(i));
    }
}

void print_bus(unsigned char value) {
    print_module("BUS", value, 31, 0);
} 
  
void print_pc(unsigned char value) {
    print_module("PC", value, 40, 1);
}
  
void print_rega(unsigned char value) {
    print_module("REGA", value, 40, 4);  
}

void print_ram(unsigned char value) {
    print_module("RAM", value, 25, 1, 22, 2);
}
  
void print_sub(unsigned char value) {
    print_module("SUB", value, 40, 7);
}
    
void print_sum(unsigned char value) {
    print_module("SUM", value, 40, 7);
}

void print_memaddr(unsigned char value) {
    print_module("MEMADDR", value, 21, 4, 22, 5);
}

void print_regb(unsigned char value) {
    print_module("REGB", value, 40, 10);  
}

void print_instr(unsigned char value) {
    print_module("INSTR", value, 23, 7, 22, 8);
}

void print_ctrlw(int controlWord) {
    print_module("CTRLW", controlWord >> 8, 23, 10, 14, 11);
    print_bin(controlWord);
}

void print_micrcntr(unsigned char value) {
    print_module("MICRCNTR", value, 20, 12, 22, 13);
}