#include "../include/solution.hpp"

Puzzle::Puzzle() {

}

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::string vectorName, std::vector<T> vec) {
    std::cout << vectorName << ": [";
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
  std::cout << "Part 1: " << fileName << std::endl;
  std::ifstream File(fileName, std::fstream::in);
  std::stringstream lineStream;
  std::string directionString;

  std::vector<std::vector<std::vector<int>>> relativeCoordinates;

  for(std::string line; std::getline(File, line);) {
    std::cout << line << std::endl;
    lineStream << line;
    std::vector<std::vector<int>> relativeCoordinateLine;

    std::vector<int> x;
    std::vector<int> y;

    while(std::getline(lineStream, directionString, ',')) {
      int distance = parseDirection(directionString);
      std::cout << "Adding " << std::to_string(distance);

      if(directionString.find('R') != std::string::npos
      || directionString.find('L') != std::string::npos) {
        x.push_back(distance);
        std::cout << " to x." << std::endl;
      }

      if(directionString.find('U') != std::string::npos
      || directionString.find('D') != std::string::npos) {
        y.push_back(distance);
        std::cout << " to y." << std::endl;
      }
    }

    printVector("x", x);
    relativeCoordinateLine.push_back(x);
    printVector("y", y);
    relativeCoordinateLine.push_back(y);
    relativeCoordinates.push_back(relativeCoordinateLine);
  }

  File.close();

  return calculateManhattanDistance(relativeCoordinates[0],
                                    relativeCoordinates[1]);
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

int parseDirection(const std::string directionString) {
  char *pDirectionString = nullptr;
  char direction = '\0';
  int distance = 0;

  sscanf(directionString.c_str(), "%c%d", &direction, &distance);

  switch(direction) {
    case 'U':
    case 'R':
      break;
    case 'D':
    case 'L':
      distance *= -1;
      break;
  }

  return distance;
}

double calculateManhattanDistance(std::vector<std::vector<int>> coordinatesP,
                                  std::vector<std::vector<int>> coordinatesQ) {
  assert(coordinatesP.size() == coordinatesQ.size());

  double distance = 0;

  for (std::vector<std::vector<int>>::size_type row_index = 0;
       row_index < coordinatesP.size();
       ++row_index) {

    if(coordinatesP[row_index].size() != coordinatesQ[row_index].size()) {
      std::cerr << "Vectors have difference sizes(p = " << std::to_string(coordinatesP[row_index].size())
                << ", q =" << std::to_string(coordinatesQ[row_index].size()) << ") at row "
                << row_index << " out of " << std::to_string(coordinatesP.size()) << std::endl;
      return distance;
    }

    for (std::vector<std::vector<int>>::size_type column_index = 0;
         column_index < coordinatesP[row_index].size();
         ++column_index) {
      distance += std::abs(coordinatesP[row_index][column_index] - coordinatesQ[row_index][column_index]);
    }
  }

  return distance;
}


int main() {
  int example0PartOneResult = partOne("example0.txt");
  std::cout << "Part One Example0 Result: " << example0PartOneResult << std::endl;
  assert(6 == example0PartOneResult);
  int example1PartOneResult = partOne("example1.txt");
  std::cout << "Part One Example1 Result: " << example1PartOneResult << std::endl;
  assert(159 == example1PartOneResult);
  int example2PartOneResult = partOne("example2.txt");
  std::cout << "Part One Example2 Result: " << example2PartOneResult << std::endl;
  assert(135 == example2PartOneResult);

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
