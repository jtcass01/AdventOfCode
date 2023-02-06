#include "../include/solution.hpp"

int calculateFuel(int mass) {
  int fuel = 0;

  fuel = (mass / 3) - 2;

  return fuel;

}

int calculateMassFuel(std::vector<int> masses) {
  int fuel = 0;

  for(int mass: masses) {
    fuel += calculateFuel(mass);
  }

  return fuel;
}

int calculateTotalFuel(std::vector<int> masses) {
  int totalFuel = 0;

  for(int mass: masses) {
    int fuel = calculateFuel(mass);

    while(fuel > 0) {
      totalFuel += fuel;
      fuel = calculateFuel(fuel);
    }
  }

  return totalFuel;

}

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  char *pLineChar = nullptr;
  std::vector<int> masses;

  for(std::string line; std::getline(File, line);) {
    std::cout << line << std::endl;
    pLineChar = strcpy(new char[line.length() + 1], line.c_str());
    masses.push_back(atoi(pLineChar));
  }

  File.close();

  return calculateMassFuel(masses);
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  char *pLineChar = nullptr;
  std::vector<int> masses;

  for(std::string line; std::getline(File, line);) {
    std::cout << line << std::endl;
    pLineChar = strcpy(new char[line.length() + 1], line.c_str());
    masses.push_back(atoi(pLineChar));
  }

  File.close();

  return calculateTotalFuel(masses);
}

int main() {
  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(3437969 == partOneResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(5154075 == partTwoResult);

  return 0;
}
