#include "../include/computer.hpp"

Computer::Computer(const std::string programFileName) {
  std::string programText;
  std::ifstream programFile;
  std::stringstream programStream;
  std::string programValue;

  programFile.open(programFileName, std::fstream::in);
  std::getline(programFile, programText);
  programStream << programText;
  while(std::getline(programStream, programValue, ',')) {
    registers_.push_back(stoi(programValue));
  }

  programFile.close();
}

Computer::Computer(std::vector<signed int> registers) : registers_(registers) {}

OPCODE Computer::injestIntcode(const Instruction instruction) {
    std::stringstream errorMessage;
    assert(instruction.size() > 0);
    const OPCODE opcode = instruction.getOpcode();
    signed int result = 0;

    switch(opcode) {
        case OPCODE::FINISHED:
            std::cout << "STOP OPCODE RECEIVED." << std::endl;
            break;
        case OPCODE::ADD:
            result = sum<signed int>(instruction.getParameters());
            write(instruction.getDestination(), result);
            break;
        case OPCODE::MULTIPLY:
            result = product<signed int>(instruction.getParameters());
            write(instruction.getDestination(), result);
            break;
        case OPCODE::WRITE:
            std::cout << std::to_string(instruction.getParameter(0)) << " input: ";
            std::cin >> result;
            write(instruction.getParameter(0), result);
            break;
        case OPCODE::READ:
            result = read(instruction.getParameter(0));
            std::cout << std::to_string(instruction.getParameter(0)) << " output: ";
            std::cout << result << std::endl;
            break;
        case OPCODE::ERROR:
        default:
            errorMessage << "Computer::injestIntcode(...) not implemented for given OPCODE: " << opcode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    return opcode;
}

void Computer::write(const unsigned int registerNumber, const signed int registerValue) {
    registers_[registerNumber] = registerValue;
}

const signed int Computer::read(const unsigned int registerNumber) const {
  return registers_[registerNumber];
}

void Computer::startUp(void) {
    OPCODE opcode = OPCODE::ERROR;
    std::vector<signed int>::iterator instructionStart = registers_.begin();
    std::cout << "Staring up computer: " << getRegisters() << std::endl;

    while(instructionStart < registers_.end()
       && opcode != OPCODE::FINISHED) {
        Instruction instruction = Instruction(&instructionStart,
                                              getRegisters());

        std::cout << "instruction: " << instruction << std::endl;
        std::cout << "\tbefore registers_ state: " << getRegisters() << std::endl;
        opcode = injestIntcode(instruction);
        std::cout << "\tafter registers_ state: " << getRegisters() << std::endl;

        *instructionStart += instruction.size();
    }
}

const std::vector<signed int> Computer::getRegisters() const {
    return registers_;
}

std::ostream &operator<<(std::ostream &os, const Computer computer) {
    const std::vector<signed int> registers_ = computer.getRegisters();
    os << registers_;
    return os;
}
