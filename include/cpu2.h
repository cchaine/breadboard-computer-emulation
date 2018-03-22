#ifndef CPU2_H
#define CPU2_H

#include "clock.h"
#include "register.h"
#include "ram.h"

void printBin(unsigned char value);

class CPU2 {
public:
    CPU2();
    ~CPU2();
    void run();

private:
    Clock * clock;
    Register * regA;
    Register * regB;
    RAM * ram;
};

#endif
