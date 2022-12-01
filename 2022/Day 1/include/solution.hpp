#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <vector>
#include <numeric>
#include <algorithm>

class Elf {
    public:
        Elf(std::vector<int> foodCalories);

        int sumCalories();

    private:
        std::vector<int> foodCalories_;
};

std::string loadFile(std::string fileName);

void loadElves(std::vector<Elf> &elves, std::string fileName);
