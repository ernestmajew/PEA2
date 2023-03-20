#include "MatrixReader.h"
#include <fstream>
#include <stdexcept>
#include <utility>

MatrixReader::MatrixReader()
        : _basePath(".\\")
{
}


AdjacencyMatrix* MatrixReader::read(std::string fileName)
{
    fileName = _basePath + fileName;
    std::ifstream file(fileName);

    if (file.fail())
        throw std::invalid_argument("Invalid file name");

    int verticesNumber = 0;

    file >> verticesNumber;
    int dataSize = verticesNumber * verticesNumber;

    int* data = new int[dataSize];
    for (size_t i = 0; i < dataSize; i++)
    {
        file >> data[i];
    }

    auto matrix = new AdjacencyMatrix(verticesNumber, data);
    delete[] data;

    return matrix;
}