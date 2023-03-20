#include "Timer.h"
void Timer::startTimer()
{
    this->reset();

    if(!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0; //milisekundy

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double Timer::stopTimer()
{
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}