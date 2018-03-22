#include "ram.h"

RAM::RAM(int size) {
   this->data = new unsigned char[size];
   this->size = size;
}

RAM::~RAM() {
    
}

unsigned char RAM::get(unsigned char address) {
    return this->data[int(address)];
}

void RAM::set(unsigned char address, unsigned char value) {
    this->data[address] = value;
}

int RAM::getSize() {
    return this->size;
}
