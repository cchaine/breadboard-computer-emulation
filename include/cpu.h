#ifndef CPU_H
#define CPU_H

#include "clock.h"
#include "register.h"
#include "ram.h"
#include "counter.h"

void printBin(unsigned char value);

class CPU {
public:
    CPU();
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
};

#endif
