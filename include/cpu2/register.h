#ifndef REGISTER_H
#define REGISTER_H

#include <cstddef>

class Register {
public:
    Register();
    ~Register();
    void set(unsigned char value);
    unsigned char get();

private:
    unsigned char value = 0;
};

#endif
