#include <algorithm>
#include "Chromosome.h"
#include "../Util/Rand.h"


void Chromosome::calculateCost(AdjacencyMatrix &matrix) {
    size_t cost = 0;
    size_t range = matrix.getVertexCount() - 1;

    for(int i = 0; i < range - 1; i++)
    {
        cost += matrix.getCost(get(i), get(i + 1));
    }
    cost += matrix.getCost(get(range - 1), get(0));

    this->_cost = cost;
}

void Chromosome::mutateSwap() {
    auto indexA = Rand::getInt(0, _vertices.size() - 2);
    auto indexB = Rand::getInt(indexA, _vertices.size() - 1);
    std::swap(_vertices[indexA], _vertices[indexB]);
}

void Chromosome::mutateReverse(){
    auto indexA = Rand::getInt(0, _vertices.size() - 2);
    auto indexB = Rand::getInt(indexA, _vertices.size() - 1);
    std::reverse(_vertices.begin() + indexA , _vertices.end() - indexB );
}