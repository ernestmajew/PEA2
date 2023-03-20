#include <fstream>
#include "SimulatedAnnealing.h"

Path* SimulatedAnnealing::solve(AdjacencyMatrix& matrix, double coolingRatio, double timeLimit){
    size_t currentCost, tempCost;
    size_t vertexCount = matrix.getVertexCount();
    double temperature = pow((double)vertexCount, 2);
    double time = 0.0, tempTime = 0.0;
    int delta;
    std::ofstream file;
    file.open(filename);

    //1. Wygenerowanie pierwszego rozwiązania
    getFirstGreedySolution(matrix);
    currentCost = _bestCost;

    //2. Główna pętla programu
    while((time / 1000.0) < timeLimit) {
        timer.startTimer();
        Array<size_t> tempVertices(_vertices);

        //2.1 Wygenerowanie nowego rozwiązania
        tempVertices = shuffleVertices(tempVertices);
        tempCost = getPathCost(matrix, tempVertices);

        delta = currentCost - tempCost;

        //2.2 Ewentualne przyjęcie gorszego rozwiązania według rozkładu boltzmana
        if(delta < 0 && !decision(delta, temperature)){
            temperature *= coolingRatio;
            time += timer.stopTimer();
            continue;
        }

        currentCost = tempCost;
        _vertices = tempVertices;
        temperature *= coolingRatio;

        //2.3 Sprawdzenie czy rozwiązanie jest lepsze
        if(currentCost < _bestCost){
            _bestPath = _vertices;
            _bestCost = currentCost;

            time += timer.stopTimer();
            file << _bestCost << ";" << time <<"\n";
            _timeFound = time;

            continue;
        }

        time += timer.stopTimer();
    }

    //3. Zwrócenie wyniku
    return new Path(_bestPath, _bestCost);
}

void SimulatedAnnealing::getFirstGreedySolution(AdjacencyMatrix& matrix){
    _vertices.addBack(0);
    size_t vertexCount = matrix.getVertexCount();

    for(int i = 0; i < vertexCount - 1; i++){
        _vertices.addBack(matrix.getLowestCostNeighbour(i, _vertices));
    }

    _bestCost = getPathCost(matrix, _vertices);
    _bestPath = _vertices;
}

size_t SimulatedAnnealing::getPathCost(AdjacencyMatrix& matrix, Array<size_t>& vertices)
{
    size_t cost = 0;
    size_t range = matrix.getVertexCount() - 1;

    for(int i = 0; i < range; i++)
    {
        cost += matrix.getCost(vertices.get(i), vertices.get(i + 1));
    }
    cost += matrix.getCost(vertices.get(range), vertices.get(0));

    return cost;
}

Array<size_t> SimulatedAnnealing::shuffleVertices(Array<size_t>& vertices) {
    vertices.swap(
            Rand::getInt(0, vertices.getSize() - 1),
            Rand::getInt(0, vertices.getSize() - 1)
            );
    return vertices;
}

bool SimulatedAnnealing::decision(int delta, double temperature){
    return Rand::getDouble(0, 1) < exp(delta / temperature);
}

