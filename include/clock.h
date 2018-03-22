#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>

class Clock {
public:
    Clock();
    Clock(float Ra, float Rb, float C);
    Clock(float frequency);
    ~Clock();
    float getFrequency();
    float getFrequency(float Ra, float Rb, float C);
    void setFrequency(float frequency);
    void waitForPulse();
    bool isHalted();
    void halt();

private:
    float frequency;
    bool stepping = false;
    bool halted = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
};

#endif
