#ifndef CPU_H
#define CPU_H

#include "clock.h"
#include "register.h"
#include "ram.h"
#include "counter.h"
#include "termcolor.hpp"

void printBin(unsigned char value);

class CPU {
public:
    CPU();
    CPU(float frequency);
    CPU(float Ra, float Rb, float C);
    ~CPU();
    void run();
    void load(unsigned char program[]);

private:
    Clock * clock;
    Register * regA;
    Register * regB;
    Register * memAddrReg;
    Register * instrReg;
    RAM * ram;
    Counter * progCntr;
    Counter * microCntr;
    void init();
};

#endif
