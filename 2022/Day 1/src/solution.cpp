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

    for(std::vector<int>::size_type maxCaloriesIndex = 0; maxCaloriesIndex != maxCalories.size(); maxCaloriesIndex++) {
      if(minimumCalories > maxCalories[maxCaloriesIndex]) {
        minimumCalories = maxCalories[maxCaloriesIndex];
        minimumCalorieIndex = maxCaloriesIndex;
      }
    }

    if(maxCalories[minimumCalorieIndex] < calories) {
      maxCalories[minimumCalorieIndex] = calories;
    }
  }

  std::cout << "maxCalories" << ": ";
  for (auto calories: maxCalories)
      std::cout << calories << ' ';
  std::cout << std::endl;

  return std::accumulate(maxCalories.begin(), maxCalories.end(), 0);
}

int partOne(const std::string fileName) {
  std::vector<Elf> exampleElves;

  loadElves(exampleElves, fileName);

  std::cout << fileName << ": ";
  for (auto elf: exampleElves)
      std::cout << elf.sumCalories() << ' ';
  std::cout << std::endl;
  std::cout << "Max: " << getMaxCalories(exampleElves) << std::endl;

  return getMaxCalories(exampleElves);
}

int partTwo(const std::string fileName) {
  std::vector<Elf> exampleElves;

  loadElves(exampleElves, fileName);

  std::cout << fileName << ": ";
  for (auto elf: exampleElves)
      std::cout << elf.sumCalories() << ' ';
  std::cout << std::endl;
  std::cout << "Top 3: " << getTopThreeCalories(exampleElves) << std::endl;

  return getTopThreeCalories(exampleElves);
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  assert(24000 == examplePartOneResult);
  int partOneResult = partOne("input.txt");
  assert(72017 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");

  return 0;
}
