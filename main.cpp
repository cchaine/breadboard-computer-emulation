#include <iostream>
#include "clock.h"

bool DEBUG = false;

void processArguments(int args, char *argv[]) {
    for(int i = 1; i < args; i++) {
        if(!strcmp(argv[i], "-d")) {
            DEBUG = true;
        }
    }
}

int main(int args, char *argv[]) {
    processArguments(args, argv);
    
    bool running = true;
    Clock * clock;
    if(DEBUG) {
        clock = new Clock();
    } else {
        clock = new Clock(220, 100, 0.000001);
    }

    int count = 0;

    while(!clock->isHalted()) {
        clock->waitForPulse();
        count++;
        if(count == 3) {
            clock->halt();
        }
    }
    
    delete(clock);
    clock = 0;
}
