#include "cpu2.h"

CPU2::CPU2() {
    this->clock = new Clock();
    this->regA = new Register();
    this->regB = new Register();
}

CPU2::~CPU2() {
    delete(this->clock);
    delete(this->regA);
    this->clock = 0;
    this->regA = 0;
}

void CPU2::run() {
    int count = 0;

    while(!this->clock->isHalted()){
        this->clock->waitForPulse();

        std::cout << int(this->regA->get()) << std::endl;
        this->regA->set(0x101);
        std::cout << int(this->regA->get()) << std::endl;

        count++;
        if(count == 2) {
            this->clock->halt();
        }
    }
}
