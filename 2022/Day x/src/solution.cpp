#include "../include/solution.hpp"

std::string loadFile(std::string fileName) {
    std::ifstream File(fileName, std::fstream::in);
    std::string str;

    // Alocate memory for file.
    File.seekg(0, std::ios::end);
    str.reserve(File.tellg());
    File.seekg(0, std::ios::beg);

    // Store file data inside str
    str.assign((std::istreambuf_iterator<char>(File)),
                std::istreambuf_iterator<char>());

    return str;
}

int partOne(const std::string fileName) {
  return 0;
}

int partTwo(const std::string fileName) {
  return 0;
}

int main() {
  std::cout << "example.txt:" << std::endl << loadFile("example.txt") << std::endl;

  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(0 == examplePartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(0 == partOneResult);

  std::cout << "input.txt:" << std::endl << loadFile("input.txt") << std::endl;
  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(0 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return 0;
}
