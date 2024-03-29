#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::vector<T> vec);

int partOne(const std::string fileName);

int partTwo(const std::string fileName);

class CommunicationDevice {
    public:
        CommunicationDevice(const std::string fileName);

        int findStartMarkerIndex(int markerSize);

    private:
        std::string fileName_;
};
