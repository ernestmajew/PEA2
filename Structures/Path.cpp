#include "Path.h"
#include <iostream>

Path::Path()
{
}

Path::Path(const Path& origin)
        : _totalCost(origin._totalCost), _vertices(origin._vertices)
{
}

Path::Path(const Array<size_t>& vertices, size_t totalCost)
        : _vertices(vertices), _totalCost(totalCost)
{
}

Path::Path(Chromosome specimen)
{
    for (int i = 0; i < specimen.size(); i++) {
        _vertices.addBack(specimen.get(i));
    }
    _totalCost = specimen.getCost();
}

void Path::print()
{
    std::cout << "Total cost: " << _totalCost << std::endl;
    _vertices.print();
}

void Path::addVertex(size_t vertex, int cost)
{
    _vertices.addFront(vertex);
    _totalCost += cost;
}

int Path::getTotalCost()
{
    return _totalCost;
}