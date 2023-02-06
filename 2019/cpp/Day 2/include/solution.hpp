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

enum OPCODE {
    FINISHED = 99,
    ADD = 1,
    MULTIPLY = 2,
    ERROR = 0
};

class Intcode {
    public:
        Intcode(const std::string programFile);

    private:
        std::vector<int> program;
};
