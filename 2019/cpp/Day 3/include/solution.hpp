#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <sstream>

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::string vectorName, std::vector<T> vec);

int partOne(const std::string fileName);

int partTwo(const std::string fileName);

int parseDirection(const std::string directionString);

double calculateManhattanDistance(std::vector<std::vector<int>> coordinatesP,
                                  std::vector<std::vector<int>> coordinatesQ);

class Puzzle {
    public:
        Puzzle();

    //private:
};
