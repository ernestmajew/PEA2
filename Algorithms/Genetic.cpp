#include <algorithm>
#include "Genetic.h"

Path* Genetic::solve(AdjacencyMatrix& matrix, size_t populationSize, double crossoverProbability, double mutationProbability, double timeLimit) {
    _mutationProbability = mutationProbability;
    _crossoverProbability = crossoverProbability;
    _populationSize = populationSize;
    size_t diversificationCounter{0}, generationCount{0};
    double time = 0.0;
    std::ofstream file;
    //file.open("genetic_48_150_SWAP.csv");


    //Generowanie pierwszej populacji
    generateInitialPopulation(matrix);

    //Warunek stopu
    while((time / 1000.0) < timeLimit) {

        timer.startTimer();

        //Aktualizacja kosztów populacji
        updatePopulationFitness(matrix);
        std::sort(_population.begin(), _population.end());

        //Sprawdzenie czy chromosom o najmniejszym koszcie w populacji ma mniejszy koszt niż globalnie najlepszy chromosom
        if(checkIfBest(_population[0])){
            diversificationCounter = 0;
            time += timer.stopTimer();
            //file << _bestChromosome.getCost() << ";" << time <<"\n";
        }
        else diversificationCounter++;

        //Funkcja dywersyfikacji
        if(diversificationCounter == noNewSolutionLimit){
            //Generowanie populacji z dywersyfikacją
            generateDiversifiedPopulationWithCrossovers(matrix);
            time += timer.stopTimer();
            continue;
        }

        //Generowanie nowej populacji
        generatePopulationWithCrossovers(matrix);
        time += timer.stopTimer();
    }
    return new Path(_bestChromosome);
}

void Genetic::generateInitialPopulation(AdjacencyMatrix &matrix) {
    Chromosome tempSpecimen;
    size_t vertexCount = matrix.getVertexCount() - 1;

    for (size_t i = 0; i < vertexCount; i++) {
        tempSpecimen.add(i);
    }

    for (size_t i = 0; i < _populationSize; i++) {
        for (size_t j = 0; j < tempSpecimen.size() / 2; j++) {
            tempSpecimen.mutateSwap();
        }
        _population.push_back(tempSpecimen);
    }
}

bool Genetic::checkIfBest(Chromosome& chromosome) {
    if(chromosome < _bestChromosome){
        _bestChromosome = chromosome;
        return true;
    }
    return false;
}

bool Genetic::makeDecision(double probability){
    return Rand::getDouble(0.0, 1.0) < probability;
}

void Genetic::generatePopulationWithCrossovers(AdjacencyMatrix &matrix) {
    //crossing
    for(size_t i = 0; i < _populationSize / 10; i++){
        if(makeDecision(_crossoverProbability)){
            Chromosome tempBest = _bestChromosome;
            crossoverPMX(tempBest, _population[i], _population[i], _population[i + 1]);
        }
    }

    for(size_t i = _populationSize / 10 - 1; i < _populationSize -1; i++){
        if(makeDecision(_crossoverProbability)){
            crossoverPMX(_population[i], _population[i + 1], _population[i], _population[i + 1]);
        }
    }

    //population mutation / swap
    if(_mutationType == mutationType::SWAP){
        for(Chromosome &specimen : _population){
            if(makeDecision(_mutationProbability)){
                specimen.mutateSwap();
            }
        }
    }

    //population mutation / reverse
    if(_mutationType == mutationType::REVERSE){
        for(Chromosome &specimen : _population){
            if(makeDecision(_mutationProbability)){
                specimen.mutateReverse();
            }
        }
    }
}

void Genetic::generateDiversifiedPopulationWithCrossovers(AdjacencyMatrix &matrix) {
    //Best 50% chromosomes are not randomized
    //Worst 50% are randomized
    for (size_t i = _populationSize / 2; i < _populationSize; i++) {
        for (size_t j = 0; j < _populationSize / 2; j++) {
            _population[i].mutateSwap();
        }
        //Cost is calculated only for new chromosomes
        _population[i].calculateCost(matrix);
    }

    //Check if any of new chromosomes is better
    std::sort(_population.begin(), _population.end());
    checkIfBest(_population[0]);

    //Crossover new population
    generatePopulationWithCrossovers(matrix);
}

void Genetic::updatePopulationFitness(AdjacencyMatrix &matrix) {
    for(Chromosome &chromosome : this->_population){
        chromosome.calculateCost(matrix);
    }
}

void Genetic::crossoverPMX(Chromosome parent1, Chromosome parent2, Chromosome& child1, Chromosome& child2) {
    std::vector<int> parent1Vertices = parent1.getVertices();
    std::vector<int> parent2Vertices = parent2.getVertices();
    std::vector<int> child1Vertices (parent1.size(), -INT_MAX);
    std::vector<int> child2Vertices (parent2.size(), -INT_MAX);

    std::vector<int> copiedFromParent1;
    std::vector<int> copiedFromParent2;

    auto indexA = Rand::getInt(0, parent1.size() - 2);
    auto indexB = Rand::getInt(indexA, parent1.size() - 1);
    int range = indexB - indexA + 1;

    for (int i = indexB; i >= indexA; --i) {
        copiedFromParent1.push_back(parent1Vertices[i]);
        copiedFromParent2.push_back(parent2Vertices[i]);
    }

    //Copying vertices from parents to new vectors
    std::copy(parent1Vertices.begin() + indexA, parent1Vertices.begin() + indexA + range, child2Vertices.begin() + indexA);
    std::copy(parent2Vertices.begin() + indexA, parent2Vertices.begin() + indexA + range, child2Vertices.begin() + indexA);

    //Copying non-conflicting vertices to new vectors
    //From parent 1
    for (int i = 0; i < parent1Vertices.size(); ++i) {
        auto found = std::find(copiedFromParent2.begin(), copiedFromParent2.end(), parent1Vertices[i]);
        if(found != copiedFromParent1.end()) child1Vertices[i] = parent1Vertices[i];
    }

    //From parent 2
    for (int i = 0; i < parent1Vertices.size(); ++i) {
        auto found = std::find(copiedFromParent1.begin(), copiedFromParent1.end(), parent2Vertices[i]);
        if(found != copiedFromParent2.end()) child2Vertices[i] = parent2Vertices[i];
    }


    //Inserting reaming vertices
    //First child
    for(int i = 0, j = 0; i < parent1.size() && j < parent1.size() ; ++i){
        if(child1Vertices[i] != -INT_MAX) continue;

        while(j < parent1.size()){
            auto found = std::find(child1Vertices.begin(), child1Vertices.end(), j);
            if(found != child1Vertices.end()){
                j++;
                continue;
            }
            break;
        }
        child1Vertices[i] = j;
        j++;
    }

    //Second child
    for(int i = 0, j = 0; i < parent1.size() && j < parent1.size() ; ++i){
        if(child2Vertices[i] != -INT_MAX) continue;

        while(j < parent1.size()){
            auto found = std::find(child2Vertices.begin(), child2Vertices.end(), j);
            if(found != child2Vertices.end()){
                j++;
                continue;
            }
            break;
        }
        child2Vertices[i] = j;
        j++;
    }

    child1.setVertices(child1Vertices);
    child2.setVertices(child2Vertices);
}




