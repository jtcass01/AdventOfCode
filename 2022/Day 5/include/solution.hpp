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

std::string partTwo(const std::string fileName);

enum CRATE_MOVER_MODEL {
    CM_9000 = 0,
    CM_9001 = 1
}

class SupplyStacks {
    public:
        SupplyStacks(const std::string fileName, CRATE_MOVER_MODEL crateMoverModel);

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
        CRATE_MOVER_MODEL crateMoverModel_;
};
