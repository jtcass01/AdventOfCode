#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

class Elf {
    public:
        Elf(std::vector<int> foodCalories);

        int sumCalories();

    private:
        std::vector<int> foodCalories_;
};

void loadElves(std::vector<Elf> &elves, const std::string fileName);

int getMaxCalories(const std::vector<Elf> elves);

int getTopThreeCalories(const std::vector<Elf> elves);

int partOne(const std::string fileName);

int partTwo(const std::string fileName);
