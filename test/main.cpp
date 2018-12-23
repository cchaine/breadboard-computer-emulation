#include <iostream>
#include "cpu.h"

bool DEBUG = false;
int frequency = -1;

int main(int args, char *argv[]) {
    for(int i = 1; i < args; i++) {
        if(!strcmp(argv[i], "-d")) {
            DEBUG = true;
        }

        if(!strcmp(argv[i], "-f")) {
            frequency = std::stoi(argv[i+1]);
            std::cout << frequency << std::endl;
        }
    }

    CPU * cpu;
    if(!DEBUG) {
        if(frequency == -1) {
            cpu = new CPU(220, 110, 0.000001);
        } else {
            cpu = new CPU(frequency);
        }
    }else {
        cpu = new CPU();
    }

    unsigned char program[] = {0x14, 0x35, 0x26, 0x0, 0xA, 0xB};

    cpu->load(program, sizeof(program));
    cpu->run();
    delete(cpu);
    cpu = 0;
}
