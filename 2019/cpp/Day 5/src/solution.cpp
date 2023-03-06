#include "../include/solution.hpp"

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;

  Computer computer(fileName, false);

  computer.startUp();

  return computer.read(0);
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;

  Computer computer(fileName, false);

  computer.startUp();

  return computer.read(0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  std::cout << "RUNNING TESTS ..." << std::endl;
  int testResult = RUN_ALL_TESTS();

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return testResult;
}
