#pragma once
#ifndef PEA2_ADJACENCYMATRIX_H
#define PEA2_ADJACENCYMATRIX_H


#include <cstdio>
#include "../Structures/Array.h"

class AdjacencyMatrix
{
public:

    AdjacencyMatrix(size_t vertexCount);
    AdjacencyMatrix(size_t verticesNumber, int* data);
    AdjacencyMatrix(const AdjacencyMatrix& origin);
    ~AdjacencyMatrix();

    void print();
    void setCost(size_t from, size_t to, int cost);
    int** getRoot();
    int getCost(size_t from, size_t to);
    int getLowestCostNeighbour(size_t from, Array<size_t> vertices);
    bool isEmpty();
    size_t getVertexCount();

private:
    size_t _vertexCount;
    int** matrix = nullptr;

    void allocateMemory();
    void insertData(int* data);
    void deallocateMemory();
    void copyData(int** data);



};


#endif //PEA2_ADJACENCYMATRIX_H
