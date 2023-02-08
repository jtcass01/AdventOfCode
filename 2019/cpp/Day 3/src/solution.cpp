#include "../include/solution.hpp"

DIRECTION charToDirection(char directionChar) {
    DIRECTION direction;

    switch(directionChar) {
      case 'U':
        direction = DIRECTION::UP;
        break;
      case 'R':
        direction = DIRECTION::RIGHT;
        break;
      case 'L':
        direction = DIRECTION::LEFT;
        break;
      case 'D':
        direction = DIRECTION::DOWN;
        break;
    }

    return direction;
}


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

    Instruction instruction = {charToDirection(directionChar),
                               magnitude};

    instructions.push_back(instruction);
  }

  return instructions;
}

Wire::Wire(std::vector<Instruction> instructions) : points_(), instructions_(instructions) {
  int x = 0;
  int y = 0;
  int distance = 0;

  for(const Instruction &instruction : instructions_) {

    switch(instruction.direction) {
      case DIRECTION::DOWN:
        for(int y_index = y; y_index >= y - instruction.magnitude; --y_index) {
          Point point = {x, y_index};
          addPoint(point);
        }
        y -= instruction.magnitude;
        break;
      case DIRECTION::UP:
        for(int y_index = y; y_index <= y + instruction.magnitude; ++y_index) {
          Point point = {x, y_index};
          addPoint(point);
        }
        y += instruction.magnitude;
        break;
      case DIRECTION::LEFT:
        for(int x_index = x; x_index >= x - instruction.magnitude; --x_index) {
          Point point = {x_index, y};
          addPoint(point);
        }
        x -= instruction.magnitude;
        break;
      case DIRECTION::RIGHT:
        for(int x_index = x; x_index <= x + instruction.magnitude; ++x_index) {
          Point point = {x_index, y};
          addPoint(point);
        }
        x += instruction.magnitude;
        break;
    }
  }
}

void Wire::addPoint(const Point point) {
  if (findPoint(point) == -1) {
    points_.push_back(point);
  }
}

int Wire::findPoint(const Point targetPoint) {
  int pointIndex = -1;

  std::vector<Point>::iterator pointIterator = std::find_if(points_.begin(),
                                                            points_.end(),
                                                            [&](const Point &point) {
    return point == targetPoint;
  });

  if (pointIterator != points_.end()) {
    pointIndex = std::distance(points_.begin(), pointIterator);
  }

  return pointIndex;
}

std::vector<Point> Wire::getPoints() const {
  return points_;
}

unsigned long Wire::countSteps(const Point targetPoint) const {
  int x = 0;
  int y = 0;
  bool pointFound = false;
  unsigned long stepCount = 0;

  for(const Instruction &instruction : instructions_) {

    switch(instruction.direction) {
      case DIRECTION::DOWN:
        for(int y_index = y-1; y_index >= y - instruction.magnitude; --y_index) {
          Point point = {x, y_index};
          stepCount++;

          if(point == targetPoint) {
            pointFound = true;
            break;
          }
        }
        y -= instruction.magnitude;
        break;
      case DIRECTION::UP:
        for(int y_index = y+1; y_index <= y + instruction.magnitude; ++y_index) {
          Point point = {x, y_index};
          stepCount++;

          if(point == targetPoint) {
            pointFound = true;
            break;
          }
        }
        y += instruction.magnitude;
        break;
      case DIRECTION::LEFT:
        for(int x_index = x-1; x_index >= x - instruction.magnitude; --x_index) {
          Point point = {x_index, y};
          stepCount++;

          if(point == targetPoint) {
            pointFound = true;
            break;
          }
        }
        x -= instruction.magnitude;
        break;
      case DIRECTION::RIGHT:
        for(int x_index = x+1; x_index <= x + instruction.magnitude; ++x_index) {
          Point point = {x_index, y};
          stepCount++;

          if(point == targetPoint) {
            pointFound = true;
            break;
          }
        }
        x += instruction.magnitude;
        break;
    }

    if(pointFound) {
      break;
    }
  }

  if(pointFound) {
    return stepCount;
  }

  return 0;
}

WireSet::WireSet(std::vector<Wire> wires) : wires_(wires) {
  for(const Wire &wire : wires) {
    const std::vector<Point> wirePoints = wire.getPoints();

    for(const Point &wirePoint : wirePoints) {
      if(wireMap_.count(wirePoint) > 0) {
        wireMap_[wirePoint] += 1;
      } else {
        wireMap_[wirePoint] = 1;
      }
    }
  }
}

long WireSet::getManhatanDistanceToClosestCross() {
  int minimum_manhattan_distance = 0;
  for (const std::pair<Point, int> &pointEntry : wireMap_) {
    if(pointEntry.second > 1) {
      Point entryPoint = pointEntry.first;
      int manhattan_distance = std::abs(entryPoint.x) + std::abs(entryPoint.y);

      if((minimum_manhattan_distance == 0 ||
          manhattan_distance < minimum_manhattan_distance)
          && manhattan_distance != 0) {
        minimum_manhattan_distance = manhattan_distance;
      }
    }
  }
  return minimum_manhattan_distance;
}

unsigned long WireSet::getMinimumSignalDelay() {
  unsigned long minimum_signal_delay = 0;

  for (const std::pair<Point, int> &pointEntry : wireMap_) {
    if(pointEntry.second > 1) {
      Point entryPoint = pointEntry.first;
      unsigned long signal_delay = 0;

      if(entryPoint.x == 0 && entryPoint.y == 0) {
        break;
      }

      for(Wire &wire : wires_) {
        signal_delay += wire.countSteps(entryPoint);
      }

      std::cout << "signal_delay: " << std::to_string(signal_delay) << std::endl;
      for(Wire &wire : wires_) {
        std::cout << "\tpointLocation: " << wire.countSteps(entryPoint) << std::endl;
      }

      if((minimum_signal_delay == 0 ||
          signal_delay < minimum_signal_delay)
          && signal_delay != 0) {
        minimum_signal_delay = signal_delay;
      }
    }
  }

  return minimum_signal_delay;
}

std::unordered_map<Point, int> WireSet::getMap() const {
  return wireMap_;
}

long partOne(const std::string fileName) {
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

unsigned long partTwo(const std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);
  std::vector<Wire> wires;

  for(std::string line; std::getline(File, line);) {
    std::vector<Instruction> wireInstructions = parseInstructions(line);
    Wire wire(wireInstructions);
    wires.push_back(wire);
  }

  File.close();

  WireSet wireSet(wires);

  return wireSet.getMinimumSignalDelay();
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
  assert(1195 == partOneResult);

  unsigned long example0PartTwoResult = partTwo("example0.txt");
  std::cout << "Part Two Example0 Result: " << example0PartTwoResult << std::endl;
  assert(30 == example0PartTwoResult);
  unsigned long example1PartTwoResult = partTwo("example1.txt");
  std::cout << "Part Two Example1 Result: " << example1PartTwoResult << std::endl;
  assert(610 == example1PartTwoResult);
  unsigned long partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(91518 == partTwoResult);

  return 0;
}
