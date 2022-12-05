#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <unordered_map>

// Function to print the elements of a vector; Written entirely by ChatGPT.
void printVector(std::vector<int> vec);

std::string partOne(const std::string fileName);

int partTwo(const std::string fileName);

class SupplyStacks {
    public:
        SupplyStacks(const std::string fileName);

        void printCrateStacks();

        void move(int crateCount, int createSource, int createDestination);

        void performRearrangementProcedure();

        std::string getTallestCrates();

    private:
        int determineStackCount();

        void initializeStacks(int stackCount);

        int convertStringIndexToStackIndex(int stringIndex);

        const std::string fileName_;
        std::unordered_map<int, std::vector<char>> crateStacks_;
};
