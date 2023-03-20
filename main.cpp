#include <fstream>
#include "Util/MatrixReader.h"
#include "Util/MatrixRandom.h"
#include "Algorithms/Genetic.h"
#include "Algorithms/SimulatedAnnealing.h"
#include "Algorithms/TabuSearch.h"


void mainMenu();
void geneticMenu();

int main() {
    geneticMenu();
}

void geneticMenu(){
    int choice, timeLimit{10}, randomSize, min, max, populationSize{150}, mutationChoice;
    double crossoverProbability{0.8}, mutationProbability{0.01}, coolingRatio = 0.90;
    std::string filename;
    MatrixReader mr;
    auto matrix = mr.read("tsp_48.txt");
    auto genetic = new Genetic;
    auto simulatedAnnealing = new SimulatedAnnealing;
    auto tabuSearch = new TabuSearch;
    auto result = genetic->solve(*matrix, populationSize, crossoverProbability, mutationProbability, 1);
    mutationType mutationType = SWAP;

    do{
        std::cout << "[ Wybor grafu ]\n"
                "[1] Wczytaj z pliku\n"
                "[2] Generuj losowo\n\n"

                "[ Algorytm Genetyczny ]\n"
                "[3] Wykonaj algorytm\n"
                "[4] Zmnien prawdopodobienstwo mutacji\n"
                "[5] Zmnien prawdopodobienstwo crossovera\n"
                "[6] Zmien limit czasu\n"
                "[7] Zmnien typ mutacji\n"
                "[8] Zmnien wielkosc populacji\n"

                "[ Symulowane wyzarzanie ]\n"
                "[9] Wykonaj algorytm\n"
                "[10] Zmnien wspolczynnik chlodzenia\n"
                "[11] Zmien limit czasu\n\n"

                "[ Tabu Serach ]\n"
                "[12] Wykonaj algorytm\n"
                "[13] Zmnien typ ruchu\n"

                "[14] Zamknij program\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Podaj nazwe pliku: \n";
                std::cin >> filename;
                    matrix = mr.read(filename);
                std::cout << "Wczytano!\n\n";
                break;

            case 2:
                std::cout << "Podaj rozmiar, wartosc minimalna, wartosc maksymalna: \n";
                std::cin >> randomSize >> min >> max;
                    matrix = MatrixRandom::generate(randomSize, min, max);
                std::cout << "Macierz wygenerowana!\n\n";
                break;

            case 3:
                genetic = new Genetic;
                genetic->selectMutationType(mutationType);
                result = genetic->solve(*matrix, populationSize, crossoverProbability, mutationProbability, timeLimit);
                result->print();
                break;

            case 4:
                std::cout << "Podaj prawdopodobienstwo:\n";
                std::cin >> mutationProbability;
                break;

            case 5:
                std::cout << "Podaj prawdopodobienstwo [s]:\n";
                std::cin >> crossoverProbability;
                break;

            case 6:
                std::cout << "Podaj limit czasu [s]:\n";
                std::cin >> timeLimit;
                break;

            case 7:
                std::cout << "Wybierz typ mutacji: [1] SWAP, [2] REVERSE\n";
                std::cin >> mutationChoice;
                if(mutationChoice == 1) mutationType = SWAP;
                if(mutationChoice == 2) mutationType = REVERSE;
                break;

            case 8:
                std::cout << "Podaj wielkosc populacji:\n";
                std::cin >> populationSize;
                break;

            case 9:
                simulatedAnnealing = new SimulatedAnnealing;
                result = simulatedAnnealing->solve(*matrix, coolingRatio, timeLimit);
                result->print();
                break;

            case 10:
                std::cout << "Podaj wspolczynnik:\n";
                std::cin >> coolingRatio;
                break;

            case 11:
                std::cout << "Podaj limit czasu [s]:\n";
                std::cin >> timeLimit;
                break;

            case 12:
                tabuSearch = new TabuSearch;
                result = tabuSearch->solve(*matrix, timeLimit);
                tabuSearch->setMoveType(moveType);
                result->print();
                break;

            case 13:
                std::cout << "Wybierz typ ruchu: [1] SWAP, [2] INSERT, [3] INVERT\n";
                std::cin >> moveChoice;
                if(moveChoice == 1) moveType = SWAP;
                if(moveChoice == 2) moveType = INSERT;
                if(moveChoice == 3) moveType = INVERT;
                break;
        }
    }while(choice != 14);
}