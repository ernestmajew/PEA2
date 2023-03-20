#ifndef PEA2_CHROMOSOME_H
#define PEA2_CHROMOSOME_H
#include <vector>
#include <climits>
#include <iostream>
#include "AdjacencyMatrix.h"

class Chromosome {
public:
    size_t getCost() const{return _cost;}
    size_t get(size_t index){return _vertices[index];}
    void set(size_t index, size_t value){_vertices[index] = value;}
    size_t size(){return _vertices.size();}
    void add(size_t value){_vertices.push_back(value);}
    void calculateCost(AdjacencyMatrix &matrix);
    std::vector<int> getVertices(){return _vertices;}
    void setVertices(std::vector<int> vertices){this->_vertices = vertices;}
    void mutateSwap();
    void mutateReverse();

    //Przeładowanie operatora dla std::sort
    bool operator < (const Chromosome& specimen) const
    {
        return this->_cost < specimen._cost;
    }

    Chromosome& operator = (const Chromosome& specimen) = default;

private:

    size_t _cost{INT_MAX};
    std::vector<int> _vertices;

};


#endif //PEA2_CHROMOSOME_H
