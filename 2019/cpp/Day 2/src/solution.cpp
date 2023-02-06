#include "../include/solution.hpp"

Intcode::Intcode(const std::string programFileName) {
  std::string programText;
  std::ifstream programFile;
  std::stringstream programStream;
  std::string programValue;

  programFile.open(programFileName, std::fstream::in);
  std::getline(programFile, programText);
  programStream << programText;
  while(std::getline(programStream, programValue, ',')) {
    program.push_back(stoi(programValue));
  }

  programFile.close();

  printVector(program);

}

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::vector<T> vec) {
    std::cout << "Vector: [";
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

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;

  Intcode intcode(fileName);

  return 0;
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;

  Intcode intcode(fileName);

  return 0;
}

int main() {
  /*int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(0 == examplePartOneResult);*/

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(3790689 == partOneResult);

  /*int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(0 == examplePartTwoResult);*/

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(6533 == partTwoResult);

  return 0;
}
