#include "../include/solution.hpp"

Rucksack::Rucksack(std::string items) {
  compartmentOne_ = items.substr(0, items.length()/2);
  compartmentTwo_ = items.substr(items.length()/2);
}

char Rucksack::getCommon() {
  size_t compartmentOneCharCount = 0;
  size_t compartmentTwoCharCount = 0;
  char commonChar = '\0';

  for(auto const & priorityMap : gv_PriorityMapping) {
    compartmentOneCharCount = std::count( compartmentOne_.begin(), compartmentOne_.end(), priorityMap.first );
    compartmentTwoCharCount = std::count( compartmentTwo_.begin(), compartmentTwo_.end(), priorityMap.first );

    if (compartmentOneCharCount > 0 && compartmentTwoCharCount > 0) {
      commonChar = priorityMap.first;
      break;
    }
  }

  return commonChar;
}

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  int prioritySum = 0;
  char commonItem = '\0';

  for(std::string line; std::getline(File, line);) {
    Rucksack rucksack(line);
    commonItem = rucksack.getCommon();
    prioritySum += gv_PriorityMapping[commonItem];
  }

  File.close();

  return prioritySum;
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  int prioritySum = 0;
  char commonItem = '\0';

  for(std::string line; std::getline(File, line);) {
    Rucksack rucksack(line);
    commonItem = rucksack.getCommon();
    prioritySum += gv_PriorityMapping[commonItem];
  }

  File.close();

  return prioritySum;
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(157 == examplePartOneResult);

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
