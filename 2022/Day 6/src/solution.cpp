#include "../include/solution.hpp"

CommunicationDevice::CommunicationDevice(const std::string fileName) {
  fileName_ = fileName;
}

int CommunicationDevice::findStartMarkerIndex(int markerSize) {
  std::ifstream File(fileName_, std::fstream::in);
  std::string line;
  std::getline(File, line);
  std::vector<char> marker;
  int lineIndex = 0;

  for(; lineIndex < line.size(); lineIndex++) {
    if(std::find(marker.begin(), marker.end(), line[lineIndex]) != marker.end()) {
      while(std::find(marker.begin(), marker.end(), line[lineIndex]) != marker.end()) {
        marker.erase(marker.begin());
      }
      marker.push_back(line[lineIndex]);
    } else {
      marker.push_back(line[lineIndex]);

      if(marker.size() == markerSize) {
        break;
      }
    }
  }

  File.close();
  return lineIndex+1;
}

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::vector<T> vec) {
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
  return device.findStartMarkerIndex(4);
}

int partTwo(const std::string fileName) {
  CommunicationDevice device(fileName);
  return device.findStartMarkerIndex(14);
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
  assert(1238 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(19 == examplePartTwoResult);

  int example0PartTwoResult = partTwo("example0.txt");
  std::cout << "Part Two Example Result: " << example0PartTwoResult << std::endl;
  assert(23 == example0PartTwoResult);

  int example1PartTwoResult = partTwo("example1.txt");
  std::cout << "Part Two Example Result: " << example1PartTwoResult << std::endl;
  assert(23 == example1PartTwoResult);

  int example2PartTwoResult = partTwo("example2.txt");
  std::cout << "Part Two Example Result: " << example2PartTwoResult << std::endl;
  assert(29 == example2PartTwoResult);

  int example3PartTwoResult = partTwo("example3.txt");
  std::cout << "Part Two Example Result: " << example3PartTwoResult << std::endl;
  assert(26 == example3PartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(3037 == partTwoResult);

  return 0;
}
