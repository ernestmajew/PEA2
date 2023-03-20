#include "MatrixRandom.h"
#include "Rand.h"

AdjacencyMatrix* MatrixRandom::generate(size_t _vertexCount, size_t _min, size_t _max)
{
    int dataSize = _vertexCount * _vertexCount;

    int* data = new int[dataSize];
    for (size_t i = 0; i < dataSize; i++)
    {
         data[i] = Rand::getInt(_min, _max);
    }

    auto matrix = new AdjacencyMatrix(_vertexCount, data);
    delete[] data;

    return matrix;
}