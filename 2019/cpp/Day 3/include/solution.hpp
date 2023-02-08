#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::string vectorName, std::vector<T> vec);

int partOne(const std::string fileName);

int partTwo(const std::string fileName);

enum DIRECTION : char {
    UP = 'U',
    RIGHT = 'R',
    LEFT = 'L',
    DOWN = 'D'
};

DIRECTION charToDirection(char directionChar) {
    DIRECTION direction;

    switch(directionChar) {
        case 'U':
            direction = DIRECTION::UP;
        case 'R':
            direction = DIRECTION::RIGHT;
        case 'L':
            direction = DIRECTION::LEFT;
        case 'D':
            direction = DIRECTION::DOWN;
    }

    return direction;
}

struct Instruction {
    DIRECTION direction;
    int magnitude;
};

std::vector<Instruction> parseInstructions(const std::string instructionString);

struct Point {
    int x;
    int y;
};

namespace std {
    template<>
    struct hash<Point> {
        std::size_t operator()(const Point &point) const {
            return std::hash<int>()(point.x) ^ std::hash<int>()(point.y);
        }
    };
}

class Wire {
    public:
        Wire(std::vector<Instruction> instructions);

        std::vector<Point> getPoints() const;

    private:
        std::vector<Point> points;
};

class WireSet {
    public:
        WireSet(std::vector<Wire> wires);

        long getManhatanDistanceToClosestCross();

    private:
        std::unordered_map<Point, int> wireMap;
};
