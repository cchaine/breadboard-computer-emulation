#include <iostream>
#include "cpu2.h"

bool DEBUG = false;

int main(int args, char *argv[]) {
    for(int i = 1; i < args; i++) {
        if(!strcmp(argv[i], "-d")) {
            DEBUG = true;
        }
    }

    CPU2 * cpu = new CPU2();

    unsigned char program[] = {0x12, 0x0, 0x1};

    cpu->load(program);
    cpu->run();
    delete(cpu);
    cpu = 0;
}
