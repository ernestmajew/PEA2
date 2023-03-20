#include <fstream>
#include "TabuSearch.h"

Path *TabuSearch::solve(AdjacencyMatrix &matrix, double timeLimit) {
    size_t currentCost;
    size_t vertexCount = matrix.getVertexCount();
    size_t sameSolutionCount{0};
    double time = 0.0;
    std::ofstream file;
    file.open(filename);
    file << "start"<<"\n";
    _cadencyLength = floor(sqrt((double)vertexCount));
    allocateTabuList(vertexCount);

    //1. Wygenerowanie pierwszego rozwiązania
    getFirstGreedySolution(matrix);
    currentCost = _bestCost;
    file << _bestCost << ";0,0" << time <<"\n";

    //2. Główna pętla programu

    while((time / 1000.0) < timeLimit){
        timer.startTimer();

        // Wykonanie ruchu
        move(matrix, currentCost);

        // Aktualizacja kadencji
        refreshTabuList(vertexCount);

        // Sprawdzenie czy nowe rozwiązanie jest lepsze
        if(currentCost < _bestCost){
            _bestPath = _vertices;
            _bestCost = currentCost;

            sameSolutionCount = 0;
            time += timer.stopTimer();
            file << _bestCost << ";" << time <<"\n";
            _timeFound = time;

            continue;
        }

        // Mechanizm dywersyfikacji
        if(sameSolutionCount > _maxSameSolutionCount){

            // Generowanie nowego losowego rozwiązania
            randomizeArray();

            sameSolutionCount = 0;
            time += timer.stopTimer();

            continue;
        }

        sameSolutionCount++;
        time += timer.stopTimer();
    }

    deallocateTabuList(vertexCount);
    //3. Zwrócenie wyniku
    return new Path(_bestPath, _bestCost);
}

void TabuSearch::move(AdjacencyMatrix &matrix, size_t &cost) {
    size_t sameSolutionCount{0}, tempCost{INT_MAX}, indexA, indexB, temp;
    boolean isWorse{true};
    Array<size_t> tempVertices(_vertices);

    while(isWorse && sameSolutionCount < _maxSameSolutionCount){

        do{
            indexA = Rand::getInt(0, _vertices.getSize() - 2);
            indexB = Rand::getInt(indexA, _vertices.getSize() - 1);
        }while(indexA == indexB||tabuList[indexA][indexB] != 0);

        switch (_moveType) {
            case moveType::SWAP: // Zamiana miejscami wartości na ideksach A i B
                _vertices.swap(indexA, indexB);
                break;

            case moveType::INSERT: // Wstawienie wartości indeksu B w miejsce indeksu A
                temp = _vertices.get(indexB);
                _vertices.removeAt(indexB);
                _vertices.addAt(indexA, temp);
                break;

            case moveType::INVERT: // Wartości w odwrotnej kolejności na indeksach od A do B
                _vertices.reverse(indexA, indexB);
                break;
        }

        tempCost = getPathCost(matrix, _vertices);

        if(tempCost < cost){
            cost = tempCost;
            isWorse = false;

            tabuList[indexA][indexB] = _cadencyLength;
        }

        sameSolutionCount++;
    }
}

void TabuSearch::getFirstGreedySolution(AdjacencyMatrix matrix){
    _vertices.addBack(0);
    size_t vertexCount = matrix.getVertexCount();

    for(int i = 0; i < vertexCount - 1; i++){
        _vertices.addBack(matrix.getLowestCostNeighbour(i, _vertices));
    }

    _bestCost = getPathCost(matrix, _vertices);
    _bestPath = _vertices;
}

void TabuSearch::randomizeArray(){
    Array<size_t> tempArray;
    int indexA, indexB;

    for(int i = 0; i < _vertices.getSize(); i++) {
        tempArray.addBack(i);
    }

    for(int i = 0; i < tempArray.getSize() / 2; i++) {
        indexA = Rand::getInt(0, _vertices.getSize() / 2);
        indexB = Rand::getInt(indexA, _vertices.getSize() - 1);
        tempArray.swap(indexA, indexB);
    }

    _vertices = tempArray;
}

size_t TabuSearch::getPathCost(AdjacencyMatrix& matrix, Array<size_t>& vertices)
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

void TabuSearch::refreshTabuList(size_t vertexCount){
    for (size_t i = 0; i < vertexCount - 1; i++)
    {
        for (size_t j = 0; j < vertexCount - 1; j++)
        {
            if(tabuList[i][j] != 0)
                tabuList[i][j]--;
        }
    }
}

void TabuSearch::allocateTabuList(size_t vertexCount) {
    if (vertexCount == 0 || tabuList != nullptr)
        throw std::runtime_error("Unable to allocate memory");

    tabuList = new size_t* [vertexCount - 1];
    for (size_t i = 0; i < vertexCount - 1; i++)
    {
            tabuList[i] = new size_t[vertexCount];
    }

    for (size_t i = 0; i < vertexCount - 1; i++)
    {
        for (size_t j = 0; j < vertexCount - 1; j++)
        {
            tabuList[i][j] = 0;
        }
    }
}

void TabuSearch::deallocateTabuList(size_t vertexCount) {
    if (tabuList == nullptr)
        return;

    for (size_t i = 0; i < vertexCount - 1; i++)
    {
        delete[] tabuList[i];
    }
    delete[] tabuList;
    tabuList = nullptr;
}

void TabuSearch::reset() {

}
