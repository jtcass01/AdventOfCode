#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::vector<T> vec);

int partOne(const std::string fileName);

int partTwo(const std::string fileName);

class Forest {
    public:
        Forest(std::string heightMapFileName);

        int countVisibleTrees();

    private:
        std::vector<std::vector<bool>> getVisibleGrid();

        std::vector<std::vector<int>> heightMap_;
};
