#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <numeric>
#include <algorithm>

int partOne(const std::string fileName);

int partTwo(const std::string fileName);

class CleanUpTasks {
    public:
        CleanUpTasks(int sectionStart, int sectionStop);

        bool contains(CleanUpTasks otherCleanUpTasks);
        bool containsAny(CleanUpTasks otherCleanUpTasks);

        std::vector<int> getSections();

    private:
        std::vector<int> sections_;
};
