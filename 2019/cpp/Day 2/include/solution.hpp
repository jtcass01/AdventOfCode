#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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

class Computer {
    public:
        Computer(const std::string programFile);

        int read(const int registerNumber);

        void write(const int registerNumber, const int registerValue);

    private:
        std::vector<int> registers;

        void startUp(void);

        OPCODE injestIntcode(const std::vector<int> instruction);
};
