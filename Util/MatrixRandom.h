#pragma once
#ifndef PEA2_MATRIXRANDOM_H
#define PEA2_MATRIXRANDOM_H


#include "../Structures/AdjacencyMatrix.h"

class MatrixRandom {

public:
    static AdjacencyMatrix* generate(size_t vertexCount, size_t min, size_t max);
};


#endif //PEA2_MATRIXRANDOM_H
