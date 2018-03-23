#include "cpu2.h"

CPU2::CPU2() {
    this->clock = new Clock();
    this->regA = new Register();
    this->regB = new Register();
    this->memAddrReg = new Register();
    this->instrReg = new Register();
    this->ram = new RAM(16);
    this->progCntr = new Counter();
    this->microCntr = new Counter();
}

CPU2::~CPU2() {
    delete(this->clock);
    delete(this->regA);
    delete(this->regB);
    delete(this->memAddrReg);
    delete(this->instrReg);
    delete(this->ram);
    delete(this->progCntr);
    delete(this->microCntr);
    this->clock = 0;
    this->regA = 0;
    this->regB = 0;
    this->memAddrReg = 0;
    this->instrReg = 0;
    this->ram = 0;
    this->progCntr = 0;
    this->microCntr = 0;
}

enum microInstructions {
    HLT = 1, 
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

int instructionSet[0x7f];

void loadInstructionSet() {
    //fetch
    for(int i = 0; i < 16; i++) {
        instructionSet[i << 3] = CO | MI;
        instructionSet[(i << 3) | 1] = RO | II | CE;
    }

    //hlt
    instructionSet[(0 << 3) | 2] = HLT;

    //lda
    instructionSet[(1 << 3) | 2] = IO | MI;
    instructionSet[(1 << 3) | 3] = RO | AI;

    //sta
    instructionSet[(2 << 3) | 2] = IO | MI;
    instructionSet[(2 << 3) | 3] = AO | RI;
   
    //add
    instructionSet[(3 << 3) | 2] = IO | MI;
    instructionSet[(3 << 3) | 3] = RO | BI;
    instructionSet[(3 << 3) | 4] = SO | AI;

}

void printInstructionSet() {
    for(int i = 0; i < 0x7f; i++) {
        std::cout << i << " ";
        printBin(instructionSet[i] >> 8);
        printBin(instructionSet[i]);
        std::cout << std::endl;
    }
}

void CPU2::run() {
    loadInstructionSet();
    std::cout << "[__RAM__] " << std::endl;
    for(int i = 0; i < this->ram->getSize(); i++) {
        printBin(this->ram->get(i));
        std::cout << std::endl;
    }

    while(!this->clock->isHalted()){
        this->clock->waitForPulse();
        
        std::cout << "____";
        printBin(((this->instrReg->get() >> 4) << 3) | (this->microCntr->get() & 0x7));
        std::cout << std::endl;
        int controlWord = 
            instructionSet[((this->instrReg->get() >> 4) << 3) | (this->microCntr->get() & 0x7)];
        unsigned char bus;

        if((controlWord & HLT) == HLT) {
            this->clock->halt();
        }
        
        if((controlWord & RO) == RO) {
            bus = this->ram->get(this->memAddrReg->get());
        }
      
        if((controlWord & IO) == IO) {
            bus = (this->instrReg->get() & 0xf);
        }
      
        if((controlWord & BO) == BO) {
            bus = this->regB->get();
        }
      
        if((controlWord & SUB) == SUB) {
            bus = this->regA->get() - this->regB->get();
        }
      
        if((controlWord & SO) == SO) {
            bus = this->regA->get() + this->regB->get();
        }
      
        if((controlWord & AO) == AO) {
            bus = this->regA->get();
        }
      
        if((controlWord & CO) == CO) {
            bus = this->progCntr->get();
        }
      
        if((controlWord & RI) == RI) {
            this->ram->set(this->memAddrReg->get(), bus);
        }
        
        if((controlWord & MI) == MI) {
            this->memAddrReg->set(bus);
        }

        if((controlWord & II) == II) {
            this->instrReg->set(bus);
        }

        if((controlWord & BI) == BI) {
            this->regB->set(bus);
        }
      
        if((controlWord & AI) == AI) {
            this->regA->set(bus);
        }

        if((controlWord & CI) == CI) {
            this->progCntr->set(bus);
        }

        if((controlWord & CE) == CE) {
            this->progCntr->enable();
        }

        this->microCntr->enable();

        std::cout << "[CTRLW] ";
        printBin(controlWord >> 8);
        printBin(controlWord);
        std::cout << std::endl;
        std::cout << "[BUS] ";
        printBin(bus);
        std::cout << std::endl;
        std::cout << "[PC] ";
        printBin(this->progCntr->get());
        std::cout << std::endl;
        std::cout << "[INSTR] ";
        printBin(this->instrReg->get());
        std::cout << std::endl;
        std::cout << "[MEMADDR] ";
        printBin(this->memAddrReg->get());
        std::cout << std::endl;
        std::cout << "[RAM] ";
        printBin(this->ram->get(this->memAddrReg->get()));
        std::cout << std::endl;
        std::cout << "[REGA] ";
        printBin(this->regA->get());
        std::cout << std::endl;
        std::cout << "[REGB] ";
        printBin(this->regB->get());
        std::cout << std::endl; 
    }
}

void CPU2::load(unsigned char program[]) {
    for(int i = 0; i < sizeof(&program); i++) {
        this->ram->set(i, program[i]);
    }
}


void printBin(unsigned char value) {
    for(int i = 0; i < 8; i++) {
        if((value & (1 << (7 - i))) != 0) {
            std::cout << "1";
        } else {
            std::cout << "0";
        }
    }
}
