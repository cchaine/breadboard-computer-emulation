#include "register.h"

Register::Register() {

}

Register::~Register() {

}

void Register::set(unsigned char value) {
    this->value = value;
}

unsigned char Register::get() {
    return this->value;
}
