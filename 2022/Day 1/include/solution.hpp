#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <vector>

class Elf {
    public:
        Elf(std::string calorieList);

        void countCalories(std::string calorieList);

    private:
        double calories;
};

std::string loadFile(std::string fileName);

void loadElves(std::vector<Elf> &elves, std::string fileName);
