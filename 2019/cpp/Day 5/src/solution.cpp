#include "../include/solution.hpp"

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;

  Computer computer(fileName);

  computer.startUp();

  return computer.read(0);
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
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(1 == examplePartOneResult);

  /// EXAMPLE 2
  std::vector<int> exampleRegisters = {1002, 4, 3, 4, 33, 99};
  Computer testComputer(exampleRegisters);
  testComputer.startUp();
  assert(testComputer.read(4) == 99);

  int partOneResult = partOne("input.txt");
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
