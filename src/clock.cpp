#include "clock.h"

Clock::Clock(float Ra, float Rb, float C) { 
    this->frequency = getFrequency(Ra, Rb, C);
    this->lastTime = std::chrono::high_resolution_clock::now();
}

Clock::Clock(float frequency) {
    this->frequency = frequency;
    this->lastTime = std::chrono::high_resolution_clock::now();
}

Clock::Clock() {
    this->stepping = true;
}

Clock::~Clock() {

}

float Clock::getFrequency() {
    return this->frequency;
}

float Clock::getFrequency(float Ra, float Rb, float C) {
    return 1.44 / ((Ra + 2*Rb)*C);
}

void Clock::setFrequency(float frequency) {
    this->frequency = frequency;
}

void Clock::waitForPulse() {
    if(this->stepping) {
        std::cout << "[__stepping__]";
        std::cin.get();
    } else {
        float deltaTime;
        float period = 1000000 / this->frequency;
        do {
            deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - this->lastTime).count();

        } while(deltaTime < period);
        this->lastTime = std::chrono::high_resolution_clock::now();
    }
    //std::cout << "clock" << std::endl;
}

bool Clock::isHalted() {
    return this->halted;
}

void Clock::halt() {
    this->halted = true;
}
