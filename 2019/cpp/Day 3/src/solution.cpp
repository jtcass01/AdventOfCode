#include "../include/solution.hpp"

std::vector<Instruction> parseInstructions(const std::string instructionString) {
  std::stringstream lineStream;
  std::string directionString;
  std::vector<Instruction> instructions;
  lineStream.str(instructionString);

  int x = 0;
  std::vector<int> xVector;
  int y = 0;
  std::vector<int> yVector;

  while(std::getline(lineStream, directionString, ',')) {
    char directionChar = '\0';
    int magnitude = 0;

    sscanf(directionString.c_str(), "%c%d", &directionChar, &magnitude);

    Instruction instruction = {charToDirection(directionChar), magnitude};

    instructions.push_back(instruction);
  }

  return instructions;
}

Wire::Wire(std::vector<Instruction> instructions) {
  int x = 0;
  int y = 0;
  int distance = 0;

  for(const Instruction &instruction : instructions) {
    Point point = {};

    switch(instruction.direction) {
      case DIRECTION::DOWN:
        for(int y_index = y; y_index >= y - instruction.magnitude; --y) {
          point = {x, y_index};
        }
        y -= instruction.magnitude;
        break;
      case DIRECTION::UP:
        for(int y_index = y; y <= y + instruction.magnitude; ++y) {
          point = {x, y_index};
        }
        y += instruction.magnitude;
        break;
      case DIRECTION::LEFT:
        for(int x_index = x; x_index >= x - instruction.magnitude; --x) {
          point = {x_index, y};
        }
        x -= instruction.magnitude;
        break;
      case DIRECTION::RIGHT:
        for(int x_index = x; x_index >= x + instruction.magnitude; ++x) {
          point = {x_index, y};
        }
        x += instruction.magnitude;
        break;
    }

    bool pointInMap = false;

    for(const Point &existingPoint : points) {
      if (existingPoint == point) {
        pointInMap = true;
        break;
      }
    }

    if(!pointInMap) {
      points.push_back(point);
    }
  }
}

std::vector<Point> Wire::getPoints() const {
  return points;
}

WireSet::WireSet(std::vector<Wire> wires) {
  for(const Wire &wire : wires) {
    const std::vector<Point> wirePoints = wire.getPoints();

    for(const Point &wirePoint : wirePoints) {
      if(wireMap.count(wirePoint) > 0) {
        wireMap[wirePoint] += 1;
      } else {
        wireMap[wirePoint] = 1;
      }
    }
  }
}

long WireSet::getManhatanDistanceToClosestCross() {
  int minimum_manhattan_distance = 0;
  for (const std::pair<Point, int> &pointEntry : wireMap) {
    if(pointEntry.second > 1) {
      Point entryPoint = pointEntry.first;
      int manhattan_distance = std::abs(entryPoint.x + entryPoint.y);

      if(minimum_manhattan_distance = 0 ||
         manhattan_distance < minimum_manhattan_distance) {
        minimum_manhattan_distance = manhattan_distance;
      }
    }
  }
  return minimum_manhattan_distance;
}

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::string vectorName, std::vector<T> vec) {
    std::cout << vectorName << ": [";
    // Loop through the vector and print each element
    for (int vector_i = 0; vector_i < vec.size(); vector_i++) {
        std::cout << vec[vector_i];

        // Add a comma after each element, except the last one
        if (vector_i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

long partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  std::vector<Wire> wires;

  for(std::string line; std::getline(File, line);) {
    std::vector<Instruction> wireInstructions = parseInstructions(line);
    Wire wire(wireInstructions);
    wires.push_back(wire);
  }

  File.close();

  WireSet wireSet(wires);

  return wireSet.getManhatanDistanceToClosestCross();
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  char *pLineChar = nullptr;

  for(std::string line; std::getline(File, line);) {
    std::cout << line << std::endl;
    pLineChar = strcpy(new char[line.length() + 1], line.c_str());
    //sscanf(pLineChar, "");
  }

  File.close();

  return 0;
}


int main() {
  long example0PartOneResult = partOne("example0.txt");
  std::cout << "Part One Example0 Result: " << example0PartOneResult << std::endl;
  assert(6 == example0PartOneResult);
  long example1PartOneResult = partOne("example1.txt");
  std::cout << "Part One Example1 Result: " << example1PartOneResult << std::endl;
  assert(159 == example1PartOneResult);
  long example2PartOneResult = partOne("example2.txt");
  std::cout << "Part One Example2 Result: " << example2PartOneResult << std::endl;
  assert(135 == example2PartOneResult);

  long partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(0 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(0 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return 0;
}
