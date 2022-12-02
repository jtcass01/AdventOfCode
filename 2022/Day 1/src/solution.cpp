#include "../include/solution.hpp"

Elf::Elf(const std::vector<int> foodCalories) {
  foodCalories_.assign(foodCalories.begin(), foodCalories.end());
}

int Elf::sumCalories() {
  return std::accumulate(foodCalories_.begin(), foodCalories_.end(), 0);
}

void loadElves(std::vector<Elf> &elves, const std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);

  std::vector<int> foodCalories;

  for(std::string line; std::getline(File, line);) {
    if (line.length() != 0) {
      int calorieCount = std::stoi(line);
      foodCalories.push_back(calorieCount);
    } else {
      Elf elf(foodCalories);
      foodCalories.clear();
      elves.push_back(elf);
    }
  }
  Elf elf(foodCalories);
  foodCalories.clear();
  elves.push_back(elf);
}

int getMaxCalories(const std::vector<Elf> elves) {
  int maxCalories = 0;

  for (auto elf: elves) {
    int calories = elf.sumCalories();

    if (calories > maxCalories) {
      maxCalories = calories;
    }
  }

  return maxCalories;
}

int getTopThreeCalories(const std::vector<Elf> elves) {
  std::vector<int> maxCalories{0, 0, 0};
  int calories = 0;
  int minimumCalories = 0;
  std::vector<int>::size_type minimumCalorieIndex = 0;

  for (auto elf: elves) {
    calories = elf.sumCalories();
    minimumCalorieIndex = 0;
    minimumCalories = maxCalories[minimumCalorieIndex];

    for(std::vector<int>::size_type maxCaloriesIndex = 0;
        maxCaloriesIndex != maxCalories.size();
        maxCaloriesIndex++) {
      if(minimumCalories > maxCalories[maxCaloriesIndex]) {
        minimumCalories = maxCalories[maxCaloriesIndex];
        minimumCalorieIndex = maxCaloriesIndex;
      }
    }

    if(maxCalories[minimumCalorieIndex] < calories) {
      maxCalories[minimumCalorieIndex] = calories;
    }
  }

  return std::accumulate(maxCalories.begin(), maxCalories.end(), 0);
}

int partOne(const std::string fileName) {
  std::vector<Elf> elves;

  loadElves(elves, fileName);

  return getMaxCalories(elves);
}

int partTwo(const std::string fileName) {
  std::vector<Elf> elves;

  loadElves(elves, fileName);

  return getTopThreeCalories(elves);
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(24000 == examplePartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(72017 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(45000 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(212520 == partTwoResult);

  return 0;
}
