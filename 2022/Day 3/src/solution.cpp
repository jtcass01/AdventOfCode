#include "../include/solution.hpp"

char getCommon(std::vector<std::string> itemContainers) {
  std::vector<size_t> itemCounts;
  char commonChar = '\0';
  bool missingItem = false;

  for(auto const & priorityMap : gv_PriorityMapping) {
    std::cout << "itemContainers: (";
    for(std::string itemContainer : itemContainers) {
      std::cout << itemContainer << ", ";
      itemCounts.emplace_back(std::count(itemContainer.begin(),
                                      itemContainer.end(),
                                      priorityMap.first));
    }
    std::cout << ")" << std::endl;

    std::cout << "Char item counts: (";
    for (size_t itemCount : itemCounts) {
      std::cout << itemCount << ", ";
      if(itemCount == 0) {
        missingItem = true;
        break;
      }
    }
    std::cout << ")" << std::endl;

    for (size_t itemCount : itemCounts) {
      if(itemCount == 0) {
        missingItem = true;
        std::cout << "Char not found: " << priorityMap.first << std::endl;
        break;
      }
    }

    if(!missingItem) {
      std::cout << "Char found in both: " << priorityMap.first << std::endl;
      commonChar = priorityMap.first;
      break;
    }

    missingItem = false;
  }

  return commonChar;
}

Items::Items(std::string items) {
  compartments_.push_back(items.substr(0, items.length()/2));
  compartments_.push_back(items.substr(items.length()/2));
}

Items::Items(std::vector<std::string> ruckSacks) {
  compartments_.assign(ruckSacks.begin(), ruckSacks.end());
}

char Items::getCommonItem() {
  return getCommon(compartments_);
}

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  int prioritySum = 0;
  char commonItem = '\0';

  for(std::string line; std::getline(File, line);) {
    Items item(line);
    commonItem = item.getCommonItem();
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
    ruckSacks.push_back(line);

    if(ruckSacks.size() == 3) {
      Items item(ruckSacks);
      commonItem = item.getCommonItem();
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
  assert(2525 == partTwoResult);

  return 0;
}
