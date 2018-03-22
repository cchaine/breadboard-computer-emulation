#ifndef CPU2_H
#define CPU2_H

#include "clock.h"
#include "register.h"
#include "ram.h"
#include "counter.h"

void printBin(unsigned char value);

class CPU2 {
public:
    CPU2();
    ~CPU2();
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
