#ifndef PEA2_TABUSEARCH_H
#define PEA2_TABUSEARCH_H

#include "../Structures/AdjacencyMatrix.h"
#include "../Structures/Array.h"
#include "../Structures/Path.h"
#include "../Util/Rand.h"
#include "../Util/Timer.h"
#include <cmath>
#include <vector>

enum moveType{
    INSERT,
    SWAP,
    INVERT
};

class TabuSearch {
public:
    Path* solve(AdjacencyMatrix& matrix, double timeLimit);
    std::string filename;

    enum moveType getMoveType(){return this->_moveType;};
    void setMoveType(enum moveType moveType){this->_moveType = moveType;};

    size_t getMaxSameSolutionCount(){return this->_maxSameSolutionCount;};
    void setMaxSameSolutionCount(size_t maxSameSolutionCount){this->_maxSameSolutionCount = maxSameSolutionCount;};

    double _timeFound{0};

private:
    moveType _moveType = SWAP;

    size_t _bestCost{INT_MAX}, _maxSameSolutionCount{50}, _cadencyLength{INT_MAX};
    size_t** tabuList = nullptr; // dwuwymiarowa tablica

    Array<size_t> _bestPath;
    Array<size_t> _vertices;
    Timer timer;




    void getFirstGreedySolution(AdjacencyMatrix matrix);
    void move(AdjacencyMatrix& matrix, size_t& cost);
    void randomizeArray();
    void allocateTabuList(size_t vertexCount);
    void deallocateTabuList(size_t vertexCount);
    void refreshTabuList(size_t vertexCount);
    void reset();
    size_t getPathCost(AdjacencyMatrix& matrix, Array<size_t>& vertices);



};


#endif //PEA2_TABUSEARCH_H
