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
            result = sum<signed int>(getInstructionParameters(instruction));
            write(instruction.getDestination(), result);
            break;
        case OPCODE::MULTIPLY:
            result = product<signed int>(getInstructionParameters(instruction));
            write(instruction.getDestination(), result);
            break;
        case OPCODE::WRITE:
            std::cout << std::to_string(instruction.getDestination()) << " input: ";
            std::cin >> result;
            write(instruction.getDestination(), result);
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

const std::vector<signed int> Computer::getInstructionParameters(const Instruction instruction) {
    std::vector<signed int> parameters = instruction.getParameters();
    std::vector<MODE> modes = instruction.getModes();

    for(signed int modeIndex = 0; modeIndex < modes.size()-1; modeIndex++) {
        if(modes[modeIndex] == MODE::POSITION) {
            parameters[modeIndex] = read(parameters[modeIndex]);
        }
    }

    return parameters;
}

void Computer::startUp(void) {
    OPCODE opcode = OPCODE::ERROR;
    std::vector<signed int>::iterator instructionStart = registers_.begin();
    std::cout << "Staring up computer: " << registers_ << std::endl;

    while(instructionStart < registers_.end()
       && opcode != OPCODE::FINISHED) {
        Instruction instruction = Instruction(&instructionStart,
                                              &registers_);

        std::cout << "\tinstruction: " << instruction << std::endl;

        opcode = injestIntcode(instruction);

        instructionStart += instruction.size();
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
