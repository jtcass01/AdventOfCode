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

enum DIRECTION : char {
    UP = 'U',
    RIGHT = 'R',
    LEFT = 'L',
    DOWN = 'D'
};

DIRECTION charToDirection(char directionChar);

struct Instruction {
    DIRECTION direction;
    int magnitude;
};

void printInstruction(const Instruction instruction);

std::vector<Instruction> parseInstructions(const std::string instructionString);

struct Point {
    int x;
    int y;
};

bool operator==(const Point &point1, const Point &point2) {
    return point1.x == point2.x && point1.y == point2.y;
}

namespace std {
    template<>
    struct hash<Point> {
        std::size_t operator()(const Point &point) const {
            std::size_t xHash = std::hash<int>{}(point.x);
            std::size_t yHash = std::hash<int>{}(point.y);

            if (xHash != yHash) {
                return xHash ^ yHash;
            }

            return xHash;
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

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::string vectorName, std::vector<T> vec);

long partOne(const std::string fileName);

int partTwo(const std::string fileName);
