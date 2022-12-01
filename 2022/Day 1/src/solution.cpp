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


int Elf::sumCalories() {
  return std::reduce(foodCalories.begin(), foodCalories.end());
}


void loadElves(std::vector<Elf> &elves, std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);

  for(std::string line; std::getline(File, line);) {
    std::vector<int> foodCalories;
    if (line.length() != 0) {
      foodCalories.push_back(std::stoi(line));
    } else {
      Elf elf(foodCalories);
      elves.push_back(elf);
      std::cout << "Elf created with calories " << elf.sumCalories() << "." << std::endl;
    }
  }
}



int main() {
  std::vector<Elf> exampleElves;

  loadElves(exampleElves, "example.txt");

  return 0;
}
