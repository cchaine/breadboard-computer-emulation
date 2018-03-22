#ifndef CPU2_H
#define CPU2_H

#include "clock.h"
#include "register.h"

class CPU2 {
public:
    CPU2();
    ~CPU2();
    void run();
private:
    Clock * clock;
    Register * regA;
};

#endif
