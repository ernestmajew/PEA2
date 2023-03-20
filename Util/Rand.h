#pragma once
#ifndef PEA2_RAND_H
#define PEA2_RAND_H


class Rand {
public:
    static int getInt(size_t min, size_t max);
    static double getDouble(size_t min, size_t max);
};


#endif //PEA2_RAND_H
