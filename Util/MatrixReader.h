#pragma once
#ifndef PEA2_MATRIXREADER_H
#define PEA2_MATRIXREADER_H


#include <string>
#include "../Structures/AdjacencyMatrix.h"

class MatrixReader
{
public:
    MatrixReader();
    AdjacencyMatrix* read(std::string fileName);

private:
    std::string _basePath;
};


#endif //PEA2_MATRIXREADER_H
