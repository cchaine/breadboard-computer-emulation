#ifndef CPU_H
#define CPU_H

#include "clock.h"
#include "register.h"
#include "ram.h"
#include "counter.h"
#include "tools.h"

enum instructionSet {
    // funct: Stops the CPU
    hlt = 0x0, 
    // funct: Loads word from the RAM in the A register
    // param: RAM address
    lda = 0x1,
    // funct: Stores word from the A register in the RAM
    // param: RAM address
    sta = 0x2,
    // funct: Adds word from the RAM with the A register and stores the result in the A register
    // param: RAM address
    add = 0x3
};

// Defines each microinstruction's bit inside the control word
enum microInstructions {
    HLT = 0x1, 
    RI = 1 << 1, 
    RO = 1 << 2,
    MI = 1 << 3, 
    II = 1 << 4, 
    IO = 1 << 5, 
    BO = 1 << 6, 
    BI = 1 << 7,
    SUB = 1 << 8,
    SO = 1 << 9,
    AO = 1 << 10,
    AI = 1 << 11,
    CI = 1 << 12,
    CO = 1 << 13,
    CE = 1 << 14
};

class CPU {
public:
    CPU();
    CPU(float frequency);
    CPU(float Ra, float Rb, float C);
    ~CPU();

    void run();
    void load(unsigned char program[], int size);

private:
    Clock * clock;
    Register * regA;
    Register * regB;
    Register * memAddrReg;
    Register * instrReg;
    RAM * ram;
    Counter * progCntr;
    Counter * microCntr;

    int controlLogic[0x7f];

    void init();
    void init_control_logic();
    void print_content(unsigned char bus, int controlWord);
};

#endif
