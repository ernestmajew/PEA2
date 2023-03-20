#include "AdjacencyMatrix.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <limits>

AdjacencyMatrix::AdjacencyMatrix(size_t vertexCount)
        : _vertexCount(vertexCount)
{
    this->allocateMemory();
}

AdjacencyMatrix::AdjacencyMatrix(size_t vertexCount, int* data)
        : _vertexCount(vertexCount)
{
    this->allocateMemory();
    this->insertData(data);
}

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& origin)
        : _vertexCount(origin._vertexCount)
{
    this->allocateMemory();
    this->copyData(origin.matrix);
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    this->deallocateMemory();
}

bool AdjacencyMatrix::isEmpty(){
    return (matrix == nullptr);
}

void AdjacencyMatrix::print()
{
    for (size_t i = 0; i < _vertexCount; i++)
    {
        std::cout << "| ";
        for (size_t j = 0; j < _vertexCount; j++)
        {
            if(i != j)
            {
                std::cout << std::setw(2) << matrix[i][j] << std::fixed << " | ";
            }
            else
            {
                std::cout << std::setw(2) << "**" << std::fixed << " | ";
            }
        }
        std::cout << std::endl;
    }
}

int** AdjacencyMatrix::getRoot()
{
    return matrix;
}

size_t AdjacencyMatrix::getVertexCount()
{
    return _vertexCount;
}

void AdjacencyMatrix::allocateMemory()
{
    if (_vertexCount == 0 || matrix != nullptr)
        throw new std::runtime_error("Unable to allocate memory");

    matrix = new int* [_vertexCount];
    for (int i = 0; i < _vertexCount; i++) {
        matrix[i] = new int[_vertexCount];
    }
}

void AdjacencyMatrix::insertData(int* data)
{
    if (_vertexCount == 0 || matrix == nullptr)
        throw new std::runtime_error("Unable to insert data to empty matrix");

    size_t dataCounter = 0;
    for (size_t i = 0; i < _vertexCount; i++)
    {
        for (size_t j = 0; j < _vertexCount; j++)
        {
            matrix[i][j] = data[dataCounter];
            dataCounter++;
        }
    }
}

void AdjacencyMatrix::deallocateMemory()
{
    if (matrix == nullptr)
        return;

    for (size_t i = 0; i < _vertexCount; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}

int AdjacencyMatrix::getCost(size_t from, size_t to)
{
    if (from >= _vertexCount || to >= _vertexCount)
        throw new std::out_of_range("Invalid vertex index");

    return matrix[from][to];
}

int AdjacencyMatrix::getLowestCostNeighbour(size_t from, Array<size_t> vertices)
{
    if (from >= _vertexCount)
        throw std::out_of_range("Invalid vertex index");

    int lowestCostNeighbour = 0, lowestCost = INT_MAX, tempCost = INT_MAX;
    for (int i = 0; i < _vertexCount; ++i) {

        if(vertices.contains(i))
        {
            continue;
        }

        tempCost = getCost(from, i);
        if(lowestCost > tempCost)
        {
            lowestCostNeighbour = i;
            lowestCost = tempCost;
        }
    }

    return lowestCostNeighbour;
}

void AdjacencyMatrix::setCost(size_t from, size_t to, int cost)
{
    if (from >= _vertexCount || to >= _vertexCount)
        throw new std::out_of_range("Invalid vertex index");

    matrix[from][to] = cost;
}

void AdjacencyMatrix::copyData(int** data)
{
    for (size_t i = 0; i < _vertexCount; i++)
    {
        for (size_t j = 0; j < _vertexCount; j++)
        {
            matrix[i][j] = data[i][j];
        }
    }
}