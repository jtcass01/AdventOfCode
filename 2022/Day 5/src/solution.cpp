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
      break;
    }
  }

  File.close();
  return stackIndex;
}

void SupplyStacks::initializeStacks(int stackCount) {

}

void SupplyStacks::performRearrangementProcedure() {

}

std::string SupplyStacks::getTallestCrates() {
  return "CMZ";
}

std::string partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;
  SupplyStacks supplyStacks(fileName);
  supplyStacks.performRearrangementProcedure();
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

  std::string partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(partOneResult.compare("") == 0);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(0 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return 0;
}
