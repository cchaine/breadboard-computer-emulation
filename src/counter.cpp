#include "counter.h"

Counter::Counter() {

}

Counter::~Counter() {

}

unsigned char Counter::get() {
    return this->value;
}

void Counter::set(unsigned char value) {
    this->value = value;
}

void Counter::enable() {
    this->value++;
}
