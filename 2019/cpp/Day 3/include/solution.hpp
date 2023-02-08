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

std::ostream &operator<<(std::ostream &os, const Instruction &instruction) {
  os << static_cast<char>(instruction.direction) << std::to_string(instruction.magnitude);
  return os;
}

std::vector<Instruction> parseInstructions(const std::string instructionString);

struct Point {
    int x;
    int y;
};

std::ostream &operator<<(std::ostream &os, const Point &point) {
  os << "(" << std::to_string(point.x) << ", " << std::to_string(point.y)  << ")";
  return os;
}

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

        void addPoint(const Point point);

        std::vector<Point> getPoints() const;

        int findPoint(const Point targetPoint);

        unsigned long countSteps(const Point targetPoint) const;

    private:
        std::vector<Point> points_;
        std::vector<Instruction> instructions_;
};

class WireSet {
    public:
        WireSet(std::vector<Wire> wires);

        long getManhatanDistanceToClosestCross();

        unsigned long getMinimumSignalDelay();

        std::unordered_map<Point, int> getMap() const;

    private:
        std::unordered_map<Point, int> wireMap_;
        std::vector<Wire> wires_;
};

std::ostream &operator<<(std::ostream &os, const WireSet &wireSet) {
    const std::unordered_map<Point, int> wireMap = wireSet.getMap();

    os << "WireSet: " << std::endl;

    for (const std::pair<Point, int> &pointEntry : wireMap) {
        os << "\t" << pointEntry.first << ": " << pointEntry.second << std::endl;
    }

    return os;
}

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> vec) {
    os << "[";
    // Loop through the vector and print each element
    for (int vector_i = 0; vector_i < vec.size(); vector_i++) {
        os << vec[vector_i];

        // Add a comma after each element, except the last one
        if (vector_i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";

    return os;
}

long partOne(const std::string fileName);

unsigned long partTwo(const std::string fileName);
