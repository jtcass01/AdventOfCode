#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::string vectorName, std::vector<T> vec);

template <typename T>
bool foundInString(std::string target, T substring);

template <typename T>
bool foundInVector(const std::vector<T> &vector, const T &element);

int partOne(const std::string fileName);

int partTwo(const std::string fileName);

enum class COMMAND {
    CHANGE_DIRECTORY,
    LIST,
    NONE
};

std::string commandToString(COMMAND command);

class DeviceSystem {
    public:
        DeviceSystem();

        void loadTerminalOutput(std::string fileName);

        int sumDirectoriesSmallerThan100KB();

        void printFiles();

    private:
        bool isCommand(std::string text);
        COMMAND getCommand(std::string text);
        std::string changeDirectory(std::string lastDirectory, std::string terminalLine);
        void addFile(std::string directoryName, std::string fileName, int fileSize);
        std::unordered_map<std::string, int> calculateDirectorySizes();
        bool withinDirectory(std::string directory, std::string filePath);

        std::unordered_map<std::string, int> files_;
        std::vector<std::string> directories_;

        char commandChar_;
        char homeChar_;
        std::string upDirectory_;
};
