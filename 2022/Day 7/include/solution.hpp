#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <unordered_map>

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::vector<T> vec);

template <typename T>
bool foundInString(std::string target, T substring);


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

        int sumDirectoriesLargerThan100KB();

    private:
        bool isCommand(std::string text);
        COMMAND getCommand(std::string text);
        std::string readCommand(std::string lastDirectory, COMMAND command, std::string terminalLine);
        void addFile(std::string fileName, int fileSize);
        int calculateSizeOfDirectory(std::string directory);

        std::unordered_map<std::string, int> fileSystem;
        char commandChar;
        char homeChar;
        std::string upDirectory;
};
