#ifndef COUNTER_H
#define COUNTER_H

#include <iostream>

class Counter {
public:
    Counter(unsigned char max);
    ~Counter();
    unsigned char get();
    void set(unsigned char value);
    void enable();
private:
    unsigned char value = 0;
    unsigned char max;
};

#endif
