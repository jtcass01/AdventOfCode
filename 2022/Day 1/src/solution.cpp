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


void loadElves(std::vector<Elf> &elves, std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);

  std::vector<int> foodCalories;

  for(std::string line; std::getline(File, line);) {
    if (line.length() != 0) {
      int calorieCount = std::stoi(line);
      std::cout << "line as int: " << calorieCount << std::endl;
    } else {
      Elf elf(foodCalories);
      foodCalories.clear();
      elves.push_back(elf);
    }
  }
}



int main() {
  std::vector<Elf> exampleElves;

  loadElves(exampleElves, "example.txt");

  std::cout << "foodCalories: ";
  for (auto elf: exampleElves)
      std::cout << elf.sumCalories() << ' ';
  std::cout << std::endl;

  return 0;
}
