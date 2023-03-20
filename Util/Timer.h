#pragma once
#ifndef PEA2_TIMER_H
#define PEA2_TIMER_H

#include <windows.h>
#include <iostream>

class Timer {

    double PCFreq = 0.0;
    __int64 CounterStart = 0;
    LARGE_INTEGER li{};

    void reset()
    {
        PCFreq = 0.0;
        CounterStart = 0;
    }

public:

    Timer() = default;

    void startTimer();
    double stopTimer();
};


#endif //PEA2_TIMER_H
