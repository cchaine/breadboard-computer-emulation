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

void printBin(unsigned char value) {
    for(int i = 0; i < 8; i++) {
        if((value & (1 << (7 - i))) != 0) {
            std::cout << "1";
        } else {
            std::cout << "0";
        }
    }
    std::cout << std::endl;
}

void CPU2::load(unsigned char program[]) {
    for(int i = 0; i < sizeof(&program); i++) {
        this->ram->set(i, program[i]);
    }
}

void CPU2::run() {
    for(int i = 0; i < this->ram->getSize(); i++) {
        std::cout << "[RAM] ";
        std::cout << "0x" << i << " ";
        printBin(this->ram->get(i));
    }

    while(!this->clock->isHalted()){
        printBin(this->progCntr->get());
        this->progCntr->enable();
        this->clock->waitForPulse();
    }
}
