#include "../include/solution.hpp"

CleanUpTasks::CleanUpTasks(int sectionStart, int sectionStop) : sections_(sectionStop-sectionStart+1) {
  std::iota(sections_.begin(), sections_.end(), sectionStart);
}

std::vector<int> CleanUpTasks::getSections() {
  return sections_;
}

bool CleanUpTasks::contains(CleanUpTasks otherCleanUpTasks) {
  std::vector<int> otherSections = otherCleanUpTasks.getSections();
  return std::includes(sections_.begin(), sections_.end(),
                       otherSections.begin(), otherSections.end());
}

bool CleanUpTasks::containsAny(CleanUpTasks otherCleanUpTasks) {
  std::vector<int> otherSections = otherCleanUpTasks.getSections();
  std::vector<int>::iterator sectionsIterator = sections_.begin();

  for(int section : otherSections) {
    sectionsIterator = std::find(sections_.begin(), sections_.end(), section);
    if(sectionsIterator == sections_.end()) {
      sectionsIterator = sections_.begin();
    } else {
      return true;
    }
  }
  return false;
}


int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  char *pLineChar = nullptr;
  int subsetCount = 0;
  int sectionOneStart = 0;
  int sectionOneStop = 0;
  int sectionTwoStart = 0;
  int sectionTwoStop = 0;

  for(std::string line; std::getline(File, line);) {
    pLineChar = strcpy(new char[line.length() + 1], line.c_str());
    sscanf(pLineChar, "%d-%d,%d-%d", &sectionOneStart, &sectionOneStop,
                                     &sectionTwoStart, &sectionTwoStop);
    CleanUpTasks sectionOne(sectionOneStart, sectionOneStop);
    CleanUpTasks sectionTwo(sectionTwoStart, sectionTwoStop);

    if(sectionOne.contains(sectionTwo) || sectionTwo.contains(sectionOne)) {
      subsetCount += 1;
    }
  }

  File.close();

  return subsetCount;
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  char *pLineChar = nullptr;
  int subsetCount = 0;
  int sectionOneStart = 0;
  int sectionOneStop = 0;
  int sectionTwoStart = 0;
  int sectionTwoStop = 0;

  for(std::string line; std::getline(File, line);) {
    std::cout << line << std::endl;
    pLineChar = strcpy(new char[line.length() + 1], line.c_str());
    sscanf(pLineChar, "%d-%d,%d-%d", &sectionOneStart, &sectionOneStop,
                                     &sectionTwoStart, &sectionTwoStop);
    CleanUpTasks sectionOne(sectionOneStart, sectionOneStop);
    CleanUpTasks sectionTwo(sectionTwoStart, sectionTwoStop);

    if(sectionOne.containsAny(sectionTwo) || sectionTwo.containsAny(sectionOne)) {
      subsetCount += 1;
    }
  }

  File.close();

  return subsetCount;
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(2 == examplePartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(580 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(4 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(895 == partTwoResult);

  return 0;
}
