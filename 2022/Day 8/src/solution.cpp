#include "../include/solution.hpp"

Forest::Forest(std::string heightMapFileName) {
  std::ifstream File(heightMapFileName, std::fstream::in);
  std::vector<int> heightRow;
  char *pLineChar = nullptr;

  for(std::string line; std::getline(File, line);) {
    for(size_t lineIndex = 0; lineIndex < line.size(); lineIndex++) {
      std::cout << line[lineIndex] << std::endl;
      heightRow.push_back(stoi(line.substr(lineIndex, 1)));
    }

    heightMap_.push_back(heightRow);
    heightRow.clear();
  }

  File.close();

  for (int vector_i = 0; vector_i < heightMap_.size(); vector_i++) {
    printVector(heightMap_[vector_i]);
  }
}

int Forest::countVisibleTrees() {
  return 0;
}

std::vector<std::vector<bool>> Forest::getVisibleGrid() {
  std::vector<std::vector<bool>> visibleGrid;

  return visibleGrid;
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
  Forest forest(fileName);
  return forest.countVisibleTrees();
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;
  Forest forest(fileName);
  return 0;
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(21 == examplePartOneResult);

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
