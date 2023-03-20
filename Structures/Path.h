#pragma once
#ifndef PEA2_PATH_H
#define PEA2_PATH_H

#include "Array.h"
#include "Chromosome.h"
#include <cstdio>

class Path
{
public:
    Path();
    Path(const Path& origin);
    Path(const Array<size_t>& vertices, size_t totalCost);
    Path(Chromosome vertices);
    void print();
    void addVertex(size_t vertex, int cost);
    int getTotalCost();

private:
    size_t _totalCost{ 0 };
    Array<size_t> _vertices;
};


#endif //PEA2_PATH_H
