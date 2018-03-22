#include "cpu2.h"

CPU2::CPU2() {
    this->clock = new Clock();
    this->regA = new Register();
    this->regB = new Register();
    this->ram = new RAM(16);
}

CPU2::~CPU2() {
    delete(this->clock);
    delete(this->regA);
    delete(this->ram);
    this->clock = 0;
    this->regA = 0;
    this->ram = 0;
}

void CPU2::run() {
    int count = 0;

    while(!this->clock->isHalted()){
        this->clock->waitForPulse();

        std::cout << int(this->regA->get()) << std::endl;
        this->regA->set(0x101);
        std::cout << int(this->regA->get()) << std::endl;

        for(int i = 0; i < this->ram->getSize(); i++) {
            printBin(this->ram->get(i));
            this->ram->set(i, 0);
        }
       
        count++;
        if(count == 2) {
            this->clock->halt();
        }
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
    std::cout << std::endl;
}
