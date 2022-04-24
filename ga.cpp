#include <iostream>
#include <string>
#include <array>
#include <random>

std::string crossover(const std::string& parentA, const std::string& parentB);
double fitness(std::string individual);
std::string mutate(std::string individual);
std::string printArray(std::array<std::string, 4> array);
std::string substring(std::string s, int start, int end);


    int random(int lo, int hi) {
    thread_local std::random_device rd;
    thread_local std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(std::min(lo, hi), std::max(lo, hi));
    return dis(gen);
}

int main() {
    std::array<std::string, 4> population;

    population[0] = "00000000";
    population[1] = "00000010";
    population[2] = "00001000";
    population[3] = "00100001";
    int generation;

    generation = 0;
    bool maximumFitnessReached;

    maximumFitnessReached = false;
    while (!maximumFitnessReached) {
        std::cout << generation << "    " << printArray(population) << std::endl;
        double bestFitness;

        bestFitness = 0;
        int bestIndex;

        bestIndex = 0;
        int secondBestIndex;

        secondBestIndex = 0;
        int i;

        for (i = 0; i <= population.size() - 1; i++) {

            double currentFitness;

            currentFitness = fitness(population[i]);
            if (currentFitness == 1.0) {
                maximumFitnessReached = true;
            } else {
                if (currentFitness >= bestFitness) {
                    bestFitness = currentFitness;
                    secondBestIndex = bestIndex;
                    bestIndex = i;
                }
            }
        }
        for (i = 0; i <= population.size() - 1; i++) {
            population[i] = mutate(crossover(population[bestIndex], population[secondBestIndex]));
        }
        generation = generation + 1;
    }
    return 0;
}

std::string crossover(const std::string& parentA, const std::string& parentB) {
    std::string child;
    int splitLength;

    splitLength = random(0, (int) parentA.length() - 1);
    child = substring(parentA, 0, splitLength) + substring(parentB, splitLength, parentB.length());

    return child;
}

double fitness(std::string individual) {
    double fitness;
    int countOfOnes;

    countOfOnes = 0;
    int i;

    for (i = 0; i <= individual.length() - 1; i++) {
        if (individual[i] == '1') {
            countOfOnes = countOfOnes + 1;
        }
    }
    fitness = (double) countOfOnes / individual.length();

    return fitness;
}

std::string mutate(std::string individual) {
    if (random(0, individual.length() - 1) % 2 == 0) {
    } else {
        int changeIndex;

        changeIndex = random(0, individual.length() - 1) % individual.length();
        std::string changedCharacter;

        if (individual[changeIndex] == '0') {
            changedCharacter = '1';
        } else {
            changedCharacter = '0';
        }
        individual = substring(individual, 0, changeIndex) + changedCharacter + substring(individual, changeIndex + 1, individual.length());
    }

    return individual;
}

std::string printArray(std::array<std::string, 4> array) {
    std::string returnString;

    returnString = "";
    int i;

    for (i = 0; i <= array.size() - 1; i++) {
        returnString = std::string(returnString) + array[i] + "    ";
    }

    return returnString;
}

std::string substring(std::string s, int start, int end) {
    std::string substring;

    substring = "";
    if (start < s.length()) {
        if (end > s.length()) {
            end = s.length();
        }
        int index;

        for (index = start; index <= end - 1; index++) {
            substring = std::string(substring) + s[index];
        }
    }

    return substring;
}
