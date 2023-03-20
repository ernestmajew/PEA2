#ifndef PEA2_SIMULATEDANNEALING_H
#define PEA2_SIMULATEDANNEALING_H

#include "../Structures/AdjacencyMatrix.h"
#include "../Structures/Array.h"
#include "../Structures/Path.h"
#include "../Util/Rand.h"
#include "../Util/Timer.h"
#include <cmath>

class SimulatedAnnealing {
public:
    Path* solve(AdjacencyMatrix& matrix, double coolingRatio, double timeLimit);
    double _timeFound;
    std::string filename;

private:
    size_t _bestCost{INT_MAX};

    Array<size_t> _bestPath;
    Array<size_t> _vertices;
    Timer timer;

    void getFirstGreedySolution(AdjacencyMatrix& matrix);
    Array<size_t> shuffleVertices(Array<size_t>& vertices);
    size_t getPathCost(AdjacencyMatrix& matrix, Array<size_t>& vertices);

    bool decision(int delta, double temperature);
};


#endif //PEA2_SIMULATEDANNEALING_H
