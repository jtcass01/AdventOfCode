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

RucksackGroup::RucksackGroup(std::vector<std::string> ruckSacks) {
  ruckSacks_.assign(ruckSacks.begin(), ruckSacks.end());
}

char RucksackGroup::getCommon() {
  size_t rucksackOneCharCount = 0;
  size_t rucksackTwoCharCount = 0;
  size_t rucksackThreeCharCount = 0;
  char commonChar = '\0';

  std::cout << "ruckSacks_[0]: " << ruckSacks_[0] << std::endl << "ruckSacks_[1]: " << ruckSacks_[1] << std::endl<< "ruckSacks_[2]: " << ruckSacks_[2] << std::endl;

  for(auto const & priorityMap : gv_PriorityMapping) {
    rucksackOneCharCount = std::count( ruckSacks_[0].begin(), ruckSacks_[0].end(), priorityMap.first );
    rucksackTwoCharCount = std::count( ruckSacks_[1].begin(), ruckSacks_[1].end(), priorityMap.first );
    rucksackThreeCharCount = std::count( ruckSacks_[2].begin(), ruckSacks_[2].end(), priorityMap.first );

    if (rucksackOneCharCount > 0 && rucksackTwoCharCount > 0 && rucksackThreeCharCount > 0) {
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
  std::vector<std::string> ruckSacks;
  int prioritySum = 0;
  char commonItem = '\0';

  for(std::string line; std::getline(File, line);) {
    std::cout << "Line " << line << " with ruckSacks.size() == " << ruckSacks.size() << std::endl;
    if(ruckSacks.size() < 3) {
      ruckSacks.push_back(line);
    } else {
      RucksackGroup ruckSackGroup(ruckSacks);
      commonItem = ruckSackGroup.getCommon();
      prioritySum += gv_PriorityMapping[commonItem];
      ruckSacks.clear();
    }
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
  assert(7581 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(70 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return 0;
}
