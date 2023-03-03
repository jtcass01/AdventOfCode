#include "../include/solution.hpp"

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;

  Computer computer(fileName);

  computer.startUp();

  return computer.read(0);
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;

  Computer computer(fileName);

  computer.startUp();

  return computer.read(0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  std::cout << "RUNNING TESTS ..." << std::endl;
  int ret{RUN_ALL_TESTS()};
  if (!ret) {
    std::cout << "<<<SUCCESS>>>" << std::endl;
  } else {
    std::cout << "FAILED" << std::endl;
  }

  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(1 == examplePartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(3 == partOneResult);

  /// EXAMPLE 0 PART 2
  std::cout << "Testing equal to in position mode. Input an 8... " << std::endl;
  std::vector<signed int> exampleEqualPosition = {3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8};
  Computer testComputerEqualPosition(exampleEqualPosition);
  testComputerEqualPosition.startUp();
  std::cout << "If you saw a 1, the test was a success." << std::endl;

  /// EXAMPLE 1 PART 2
  std::cout << "Testing less than in position mode. Input a value less than 8... " << std::endl;
  std::vector<signed int> exampleLessThanPosition = {3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8};
  Computer testComputerLessThanPosition(exampleLessThanPosition);
  testComputerLessThanPosition.startUp();
  std::cout << "If you saw a 1, the test was a success." << std::endl;

  /// EXAMPLE 2 PART 2
  std::cout << "Testing equal to in immediate mode. Input an 8... " << std::endl;
  std::vector<signed int> exampleEqualImmediate = {3, 3, 1108, -1, 8, 3, 4, 3, 99};
  Computer testComputerEqualImmediate(exampleEqualImmediate);
  testComputerEqualImmediate.startUp();
  std::cout << "If you saw a 1, the test was a success." << std::endl;

  /// EXAMPLE 3 PART 2
  std::cout << "Testing less than in immediate mode. Input a value less than 8... " << std::endl;
  std::vector<signed int> exampleLessThanImmediate = {3, 3, 1107, -1, 8, 3, 4, 3, 99};
  Computer testComputerLessThanImmediate(exampleLessThanImmediate);
  testComputerLessThanImmediate.startUp();
  std::cout << "If you saw a 1, the test was a success." << std::endl;

  std::cout << "Testing jump in position mode. Expect a 1 if the value is nonzero or a 0 if the value is 0..." << std::endl;
  std::vector<signed int> exampleJumpPosition = {3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9};
  Computer testComputerJumpPosition(exampleJumpPosition);
  testComputerJumpPosition.startUp();

  std::cout << "Testing jump in immediate mode. Expect a 1 if the value is nonzero or a 0 if the value is 0..." << std::endl;
  std::vector<signed int> exampleJumpImmediate = {3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1};
  Computer testComputerJumpImmediate(exampleJumpImmediate);
  testComputerJumpImmediate.startUp();

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return 0;
}
