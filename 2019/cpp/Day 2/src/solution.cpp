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
}

void Computer::startUp(void) {
  OPCODE opCode = OPCODE::ERROR;

  for(std::vector<double>::iterator instructionStart = registers.begin();
      instructionStart < registers.end(); instructionStart += 4) {
    std::vector<double>::iterator instructionEnd = instructionStart + 4;
    std::vector<double> instruction(instructionStart, instructionEnd);
    opCode = injestIntcode(instruction);

    if (opCode == OPCODE::FINISHED) {
      break;
    }
  }
}

OPCODE Computer::injestIntcode(const std::vector<double> instruction) {
  assert(instruction.size() == 4);

  OPCODE opcode = static_cast<OPCODE>(instruction[0]);
  double registerOneValue = 0;
  double registerTwoValue = 0;

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

double Computer::read(const int registerNumber) {
  return registers[registerNumber];
}

void Computer::write(const int registerNumber, const double registerValue) {
  registers[registerNumber] = registerValue;
}

void Computer::printRegisters() {
  printVector(registers);
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
  int result = 0;

  for (int noun = 0; noun < 100; noun++) {
    for(int verb = 0; verb < 100; verb++) {
      Computer computer(fileName);
      computer.write(1, noun);
      computer.write(2, verb);

      computer.startUp();

      if(computer.read(0) == 19690720) {
        result = 100 * noun + verb;
        break;
      }
    }
    if(result != 0) {
      break;
    }
  }

  return result;
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(100 == examplePartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(3790689 == partOneResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(6533 == partTwoResult);

  return 0;
}
