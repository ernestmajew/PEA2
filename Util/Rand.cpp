#include <cstdio>
#include <random>
#include "Rand.h"

int Rand::getInt(size_t min, size_t max)
{
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> values(min, max);

    return values(gen);
}

double Rand::getDouble(size_t min, size_t max)
{
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_real_distribution<double> values(min, max);

    return values(gen);
}