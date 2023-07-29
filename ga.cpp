#include <iostream>
#include <string>
#include <array>
#include <random>

const int MAX_GENERATIONS = 1000;  // to prevent infinite loops

std::string crossover(const std::string& parentA, const std::string& parentB);
double fitness(const std::string& individual);
std::string mutate(const std::string& individual);
std::string printArray(const std::array<std::string, 4>& arr);

int random(int lo, int hi) {
    thread_local std::random_device rd;
    thread_local std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(std::min(lo, hi), std::max(lo, hi));
    return dis(gen);
}

int main() {
    std::array<std::string, 4> population = {"00000000", "00000010", "00001000", "00100001"};
    int generation = 0;

    while (generation < MAX_GENERATIONS) {
        std::cout << generation << "    " << printArray(population) << std::endl;
        double bestFitness = 0;
        int bestIndex = 0;
        int secondBestIndex = 0;

        for (int i = 0; i < population.size(); i++) {
            double currentFitness = fitness(population[i]);
            if (currentFitness == 1.0) {
                std::cout << "Maximum fitness reached!" << std::endl;
                return 0;
            } else {
                if (currentFitness > bestFitness) {
                    secondBestIndex = bestIndex;
                    bestFitness = currentFitness;
                    bestIndex = i;
                }
            }
        }

        for (int i = 0; i < population.size(); i++) {
            population[i] = mutate(crossover(population[bestIndex], population[secondBestIndex]));
        }
        generation++;
    }

    std::cout << "Max generations reached without achieving maximum fitness." << std::endl;
    return 0;
}

std::string crossover(const std::string& parentA, const std::string& parentB) {
    int splitLength = random(0, parentA.length() - 1);
    return parentA.substr(0, splitLength) + parentB.substr(splitLength);
}

double fitness(const std::string& individual) {
    int countOfOnes = 0;

    for (char c : individual) {
        if (c == '1') {
            countOfOnes++;
        }
    }

    return static_cast<double>(countOfOnes) / individual.length();
}

std::string mutate(const std::string& individual) {
    if (random(0, 1) == 0) {
        return individual; // no mutation
    }
    
    int changeIndex = random(0, individual.length() - 1);
    char changedCharacter = (individual[changeIndex] == '0') ? '1' : '0';
    return individual.substr(0, changeIndex) + changedCharacter + individual.substr(changeIndex + 1);
}

std::string printArray(const std::array<std::string, 4>& arr) {
    std::string result;

    for (const auto& s : arr) {
        result += s + "    ";
    }

    return result;
}
