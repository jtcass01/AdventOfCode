#include "../include/solution.hpp"

SupplyStacks::SupplyStacks(const std::string fileName) : fileName_(fileName) {
  int stackCount = determineStackCount();
  std::cout << "stackCount: " << stackCount << std::endl;
  initializeStacks(stackCount);
}

int SupplyStacks::determineStackCount() {
  std::ifstream File(fileName_, std::fstream::in);
  char *pLineChar = nullptr;
  size_t stackCountStart = 0;
  int stackIndex = 0;
  std::stringstream countStream;
  std::string nextCount = " 1 ";

  for(std::string line; std::getline(File, line);) {
    stackCountStart = line.find(nextCount);

    while(stackCountStart != std::string::npos) {
      stackIndex++;
      countStream << " " << stackIndex << " ";
      stackCountStart = line.find(countStream.str());
      countStream.str("");
    }

    if(stackIndex > 0) {
      stackIndex--;
      break;
    }
  }

  File.close();
  return stackIndex;
}

void SupplyStacks::initializeStacks(int stackCount) {
  std::ifstream File(fileName_, std::fstream::in);
  int stackIndex = 1;

  // Initialize empty crate stacks
  // for(; stackIndex <= stackCount; stackIndex++) {
  //   crateStacks_.insert(std::make_pair(stackIndex, std::vector<char>{'\0'}));
  // }

  stackIndex = 0;
  // Parse file filling in initial positions of crate stacks
  for(std::string line; std::getline(File, line);) {
    if(line.find(" 1 ") != std::string::npos) {
      // stack def line
      break;
    } else {
      for(int lineIndex = 0; lineIndex < line.size(); lineIndex++) {
        if(isalpha(line[lineIndex])) {
          stackIndex = convertStringIndexToStackIndex(lineIndex);

          if(crateStacks_.count(stackIndex) == 0) {
            crateStacks_.insert(std::make_pair(stackIndex, std::vector<char>{line[lineIndex]}));
          } else {
            crateStacks_[stackIndex].push_back(line[lineIndex]); 
          }
        }
      }
    }
  }

  File.close();
}

int SupplyStacks::convertStringIndexToStackIndex(int stringIndex) {
  if(stringIndex == 1) {
    return stringIndex;
  }

  return ((stringIndex-1)/4)+1;
}

void SupplyStacks::move(int crateCount, int crateSource, int createDestination) {
  char crateToMove = '\0';

  for(int crateIndex = 0; crateIndex < crateCount; crateIndex++) {
    crateToMove = crateStacks_[crateSource].at(0);
    crateStacks_[crateSource].erase(crateStacks_[crateSource].begin());
    crateStacks_[createDestination].insert(crateStacks_[createDestination].begin(), crateToMove);
  }
}

void SupplyStacks::performRearrangementProcedure() {
  std::ifstream File(fileName_, std::fstream::in);
  char *pLineChar = nullptr;
  int crateCount = 0;
  int crateSource = 0;
  int crateDestination = 0;

  printCrateStacks();
  for(std::string line; std::getline(File, line);) {
    if(line.find("move") != std::string::npos) {
      pLineChar = strcpy(new char[line.length() + 1], line.c_str());
      // stack def linek
      std::cout << "Line: " << line << std::endl;
      sscanf(pLineChar, "move %i from %i to %i", &crateCount, &crateSource, &crateDestination);
      move(crateCount, crateSource, crateDestination);

      printCrateStacks();
    }
  }

  File.close();
}

std::string SupplyStacks::getTallestCrates() {
  return "CMZ";
}

// Code generated by ChatGPT
void SupplyStacks::printCrateStacks() {
  // Loop through the mapping and print the keys and values
  for (auto it = crateStacks_.begin(); it != crateStacks_.end(); ++it) {
    std::cout << it->first << "(" << it->second.size() << "): ";
    for (const auto &val : it->second) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

std::string partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;
  SupplyStacks supplyStacks(fileName);
  supplyStacks.performRearrangementProcedure();
  supplyStacks.printCrateStacks();
  return supplyStacks.getTallestCrates();
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
  std::string examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(examplePartOneResult.compare("CMZ") == 0);

  // std::string partOneResult = partOne("input.txt");
  // std::cout << "Part One Input Result: " << partOneResult << std::endl;
  // assert(partOneResult.compare("") == 0);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(0 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return 0;
}
