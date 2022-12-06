#include "../include/solution.hpp"

CommunicationDevice::CommunicationDevice(const std::string fileName) {
  fileName_ = fileName;
}

int CommunicationDevice::findStartMarkerIndex() {
  std::ifstream File(fileName_, std::fstream::in);
  std::string line;
  std::getline(File, line);
  std::vector<char> marker;
  int lineIndex = 0;

  for(; lineIndex < line.size(); lineIndex++) {
    if(std::find(marker.begin(), marker.end(), line[lineIndex]) != marker.end()) {
      marker.clear();
    } else {
      marker.push_back(line[lineIndex]);

      if(marker.size() == 4) {
        break;
      }
    }
  }

  File.close();
  return lineIndex;
}

// Function to print the elements of a vector; Written entirely by ChatGPT.
void printVector(std::vector<int> vec) {
    std::cout << "Vector: [";
    // Loop through the vector and print each element
    for (int vector_i = 0; vector_i < vec.size(); vector_i++) {
        std::cout << vec[vector_i];

        // Add a comma after each element, except the last one
        if (vector_i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int partOne(const std::string fileName) {
  CommunicationDevice device(fileName);
  return device.findStartMarkerIndex();
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  char *pLineChar = nullptr;

  for(std::string line; std::getline(File, line);) {
    std::cout << line << std::endl;
    pLineChar = strcpy(new char[line.length() + 1], line.c_str());
    //sscanf(pLineChar, "");
  }

  File.close();

  return 0;
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(7 == examplePartOneResult);

  int example0PartOneResult = partOne("example0.txt");
  std::cout << "Part One Example Result: " << example0PartOneResult << std::endl;
  assert(5 == example0PartOneResult);

  int example1PartOneResult = partOne("example1.txt");
  std::cout << "Part One Example Result: " << example1PartOneResult << std::endl;
  assert(6 == example1PartOneResult);

  int example2PartOneResult = partOne("example2.txt");
  std::cout << "Part One Example Result: " << example2PartOneResult << std::endl;
  assert(10 == example2PartOneResult);

  int example3PartOneResult = partOne("example3.txt");
  std::cout << "Part One Example Result: " << example3PartOneResult << std::endl;
  assert(11 == example3PartOneResult);

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
