#ifndef COUNTER_H
#define COUNTER_H

class Counter {
public:
    Counter();
    ~Counter();
    unsigned char get();
    void set(unsigned char value);
    void enable();
private:
    unsigned char value = 0;
};

#endif
