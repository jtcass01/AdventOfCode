#include "../include/solution.hpp"

Computer::Computer(const std::string programFileName) {
  std::string programText;
  std::ifstream programFile;
  std::stringstream programStream;
  std::string programValue;

  programFile.open(programFileName, std::fstream::in);
  std::getline(programFile, programText);
  programStream << programText;
  while(std::getline(programStream, programValue, ',')) {
    registers.push_back(stoi(programValue));
  }

  programFile.close();

  printVector(registers);
}

void Computer::startUp(void) {
  for(std::vector<int>::iterator instructionStart = registers.begin();
      instructionStart < registers.end(); instructionStart += 4) {
    std::vector<int>::iterator instructionEnd = instructionStart + 4;
    std::vector<int> instruction(instructionStart, instructionEnd);

    if (injestIntcode(instruction) == OPCODE::FINISHED) {
      break;
    }
  }
}

OPCODE Computer::injestIntcode(const std::vector<int> instruction) {
  assert(instruction.size() == 4);

  OPCODE opcode = static_cast<OPCODE>(instruction[0]);
  int registerOneValue = 0;
  int registerTwoValue = 0;

  switch(opcode) {
    case OPCODE::FINISHED:
      break;
    case OPCODE::ADD:
      registerOneValue = read(instruction[1]);
      registerTwoValue = read(instruction[2]);
      write(instruction[3], registerOneValue + registerTwoValue);
      break;
    case OPCODE::MULTIPLY:
      registerOneValue = read(instruction[1]);
      registerTwoValue = read(instruction[2]);
      write(instruction[3], registerOneValue * registerTwoValue);
      break;
    default:
      break;
  }

  return opcode;
}

int Computer::read(const int registerNumber) {
  return registers[registerNumber];
}

void Computer::write(const int registerNumber, const int registerValue) {
  registers[registerNumber] = registerValue;
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
  std::cout << "Part 1: " << fileName << std::endl;

  Computer computer(fileName);

  computer.write(1, 12);
  computer.write(2, 2);

  computer.startUp();

  return computer.read(0);
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;

  Computer computer(fileName);

  return 0;
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(3500 == examplePartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(3790689 == partOneResult);

  /*int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(0 == examplePartTwoResult);*/

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(6533 == partTwoResult);

  return 0;
}
