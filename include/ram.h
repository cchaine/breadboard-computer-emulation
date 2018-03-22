#ifndef RAM_H
#define RAM_H

#include <iostream>

class RAM {
public:
    RAM(int size);
    ~RAM();
    unsigned char get(unsigned char address);
    void set(unsigned char address, unsigned char value);
    int getSize();
private:
    int size;
    unsigned char *data;
};

#endif
