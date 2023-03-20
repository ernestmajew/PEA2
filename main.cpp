#include <fstream>
#include "Util/MatrixReader.h"
#include "Util/MatrixRandom.h"
#include "Algorithms/Genetic.h"


using namespace std;

// TODO
// Wczytanie z pliku [+]
// Czas stopu [+]

// Algorytm SW [+]
// Wspolczynnik zmiany temperatury [+]

// Algorytm TS [+]
// Wybor sasiedztwa [+]

// Algorytm genetyczny [+]
// Menu do GA [+]
// Ustawianie parametrów [+]

void mainMenu();
void geneticMenu();

int main() {
    geneticMenu();
}

void geneticMenu(){
    int choice, timeLimit{10}, randomSize, min, max, populationSize{150}, mutationChoice;
    double crossoverProbability{0.8}, mutationProbability{0.01};
    string filename;
    MatrixReader mr;
    auto matrix = mr.read("tsp_48.txt");
    auto genetic = new Genetic;
    auto result = genetic->solve(*matrix, populationSize, crossoverProbability, mutationProbability, 1);
    mutationType mutationType = SWAP;

    do{
        cout << "[ Wybor grafu ]\n"
                "[1] Wczytaj z pliku\n"
                "[2] Generuj losowo\n\n"
                "[ Algorytm ]\n"
                "[3] Wykonaj algorytm\n"
                "[4] Zmnien prawdopodobienstwo mutacji\n"
                "[5] Zmnien prawdopodobienstwo crossovera\n"
                "[6] Zmien limit czasu\n"
                "[7] Zmnien typ mutacji\n"
                "[8] Zmnien wielkosc populacji\n"

                "[9] Zamknij program\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Podaj nazwe pliku: \n";
                cin >> filename;
                    matrix = mr.read(filename);
                cout << "Wczytano!\n\n";
                break;

            case 2:
                cout << "Podaj rozmiar, wartosc minimalna, wartosc maksymalna: \n";
                cin >> randomSize >> min >> max;
                    matrix = MatrixRandom::generate(randomSize, min, max);
                cout << "Macierz wygenerowana!\n\n";
                break;

            case 3:
                genetic = new Genetic;
                genetic->selectMutationType(mutationType);
                result = genetic->solve(*matrix, populationSize, crossoverProbability, mutationProbability, timeLimit);
                result->print();
                break;

            case 4:
                cout << "Podaj prawdopodobienstwo:\n";
                cin >> mutationProbability;
                break;

            case 5:
                cout << "Podaj prawdopodobienstwo [s]:\n";
                cin >> crossoverProbability;
                break;

            case 6:
                cout << "Podaj limit czasu [s]:\n";
                cin >> timeLimit;
                break;

            case 7:
                cout << "Wybierz typ mutacji: [1] SWAP, [2] REVERSE\n";
                cin >> mutationChoice;
                if(mutationChoice == 1) mutationType = SWAP;
                if(mutationChoice == 2) mutationType = REVERSE;
                break;

            case 8:
                cout << "Podaj wielkosc populacji:\n";
                cin >> populationSize;
                break;

        }
    }while(choice != 9);
}

//void mainMenu(){
//    int choice, moveChoice, time = 10, randomSize, min, max;
//    double  coolingRatio = 0.90;
//    string filename;
//    MatrixReader mr;
//    auto matrix = mr.read("tsp_48.txt");
//    auto simulatedAnnealing = new SimulatedAnnealing;
//    auto tabuSearch = new TabuSearch;
//    auto result = tabuSearch->solve(*matrix, 1);
//    moveType moveType = SWAP;
//
//    do{
//        cout << "[ Wybor grafu ]\n"
//                "[1] Wczytaj z pliku\n"
//                "[2] Generuj losowo\n\n"
//                "[ Symulowane wyzarzanie ]\n"
//                "[3] Wykonaj algorytm\n"
//                "[4] Zmnien wspolczynnik chlodzenia\n"
//                "[5] Zmien limit czasu\n\n"
//                "[ Tabu Serach ]\n"
//                "[6] Wykonaj algorytm\n"
//                "[7] Zmnien typ ruchu\n"
//                "[9] Zamknij program\n";
//        cin >> choice;
//
//        switch (choice) {
//            case 1:
//                cout << "Podaj nazwe pliku: \n";
//                cin >> filename;
//                    matrix = mr.read(filename);
//                cout << "Wczytano!\n\n";
//                break;
//
//            case 2:
//                cout << "Podaj rozmiar, wartosc minimalna, wartosc maksymalna: \n";
//                cin >> randomSize >> min >> max;
//                    matrix = MatrixRandom::generate(randomSize, min, max);
//                cout << "Macierz wygenerowana!\n\n";
//                break;
//
//            case 3:
//                simulatedAnnealing = new SimulatedAnnealing;
//                result = simulatedAnnealing->solve(*matrix, coolingRatio, time);
//                result->print();
//                break;
//
//            case 4:
//                cout << "Podaj wspolczynnik:\n";
//                cin >> coolingRatio;
//                break;
//
//            case 5:
//                cout << "Podaj limit czasu [s]:\n";
//                cin >> time;
//                break;
//
//            case 6:
//                tabuSearch = new TabuSearch;
//                result = tabuSearch->solve(*matrix, time);
//                tabuSearch->setMoveType(moveType);
//                result->print();
//                break;
//
//            case 7:
//                cout << "Wybierz typ ruchu: [1] SWAP, [2] INSERT, [3] INVERT\n";
//                cin >> moveChoice;
//                if(moveChoice == 1) moveType = SWAP;
//                if(moveChoice == 1) moveType = INSERT;
//                if(moveChoice == 1) moveType = INVERT;
//                break;
//
//        }
//    }while(choice != 9);
//}