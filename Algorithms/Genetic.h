#ifndef PEA2_GENETIC_H
#define PEA2_GENETIC_H

#include <vector>
#include "../Structures/Path.h"
#include "../Structures/AdjacencyMatrix.h"
#include "../Util/Timer.h"
#include "../Util/Rand.h"
#include "../Structures/Chromosome.h"
#include <fstream>

enum mutationType{
    SWAP,
    REVERSE
};

class Genetic {
public:
    Path* solve(AdjacencyMatrix& matrix, size_t populationSize, double crossoverProbability, double mutationProbability, double timeLimit);
    void selectMutationType(enum mutationType mutationType){
        this->_mutationType = mutationType;
    };

private:
    double _crossoverProbability;
    double _mutationProbability;

    size_t _populationSize;
    size_t noNewSolutionLimit{100000};

    mutationType _mutationType = SWAP;

    std::vector<Chromosome> _population;
    Chromosome _bestChromosome;

    Timer timer;

    void generatePopulationWithCrossovers(AdjacencyMatrix &matrix);
    void generateDiversifiedPopulationWithCrossovers(AdjacencyMatrix &matrix);
    void generateInitialPopulation(AdjacencyMatrix& matrix);
    void updatePopulationFitness(AdjacencyMatrix& matrix);
    void crossoverPMX(Chromosome parent1, Chromosome parent2, Chromosome& child1, Chromosome& child2);
    bool checkIfBest(Chromosome& chromosome);
    static bool makeDecision(double probability);
};

#endif //PEA2_GENETIC_H
