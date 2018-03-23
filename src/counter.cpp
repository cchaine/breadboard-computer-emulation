#include "counter.h"

Counter::Counter(unsigned char max) {
    this->max = max;
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
    if(this->value > max){
        this->value = 0;
    }
}
