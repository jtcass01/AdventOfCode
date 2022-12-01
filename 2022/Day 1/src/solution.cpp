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
  std::cout << "foodCalories: ";
  for (auto foodCalorie: foodCalories)
      std::cout << foodCalorie << ' ';
  std::cout << std::endl;

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
    } else {
      Elf elf(foodCalories);
      foodCalories.clear();
      std::cout << "Elf: " << elf.sumCalories() << std::endl;
      elves.push_back(elf);
    }
  }

  std::cout << "exampleElves: ";
  for (int i=0; i < 4; i++)
      std::cout << elves[i].sumCalories() << ' ';
  std::cout << std::endl;
}



int main() {
  std::vector<Elf> exampleElves;

  loadElves(exampleElves, "example.txt");

  std::cout << "exampleElves: ";
  for (auto elf: exampleElves)
      std::cout << elf.sumCalories() << ' ';
  std::cout << std::endl;

  return 0;
}
