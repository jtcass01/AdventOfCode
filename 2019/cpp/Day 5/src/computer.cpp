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

std::vector<signed int>::iterator Computer::injestIntcode(const Instruction instruction) {
    std::stringstream errorMessage;
    assert(instruction.size() > 0);
    const OPCODE opcode = instruction.getOpcode();
    // std::cout << "OPCODE = "<< opcode << std::endl;
    signed int result = 0;
    std::vector<signed int> instructionParameters = getInstructionParameters(instruction);
    const signed int destination = getDestination(instruction);

    std::cout << "instructionParameters = "<< instructionParameters << std::endl;
    std::cout << "destination = "<< destination << std::endl;

    switch(opcode) {
        case OPCODE::FINISHED:
            std::cout << "STOP OPCODE RECEIVED." << std::endl;
            break;
        case OPCODE::ADD:
            result = sum<signed int>(instructionParameters);
            write(destination, result);
            break;
        case OPCODE::MULTIPLY:
            result = product<signed int>(instructionParameters);
            write(destination, result);
            break;
        case OPCODE::WRITE:
            std::cout << std::to_string(destination) << " input: ";
            std::cin >> result;
            write(destination, result);
            break;
        case OPCODE::READ:
            result = read(instructionParameters[0]);
            std::cout << std::to_string(instructionParameters[0]) << " output: ";
            std::cout << result << std::endl;
            break;
        case OPCODE::JUMP_IF_TRUE:
            result = instructionParameters[0];

            if (result != 0) {
                return registers_.begin() + destination;
            }

            break;
        case OPCODE::JUMP_IF_FALSE:
            result = instructionParameters[0];

            if (result == 0) {
                return registers_.begin() + destination;
            }

            break;
        case OPCODE::LESS_THAN:
            if(instructionParameters[0] < instructionParameters[1]) {
                write(destination, 1);
            } else {
                write(destination, 0);
            }
            break;
        case OPCODE::EQUALS:
            std::cout << std::to_string(instructionParameters[0]) << " == ";
            std::cout << std::to_string(instructionParameters[1]) << " = ";
            std::cout << std::to_string(instructionParameters[0] == instructionParameters[1]);
            std::cout << std::endl;

            if(instructionParameters[0] == instructionParameters[1]) {
                write(destination, 1);
            } else {
                write(destination, 0);
            }
            break;
        case OPCODE::ERROR:
        default:
            errorMessage << "Computer::injestIntcode(...) not implemented for given OPCODE: " << opcode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    if(opcode == OPCODE::FINISHED) {
        return registers_.end();
    }

    return instruction.getParametersStart()+instruction.size()-1;
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

    if(parameters.size() == 0) {
        return parameters;
    }

    for(signed int modeIndex = 0; modeIndex < modes.size()-1; modeIndex++) {
        if(modes[modeIndex] == MODE::POSITION) {
            parameters[modeIndex] = read(parameters[modeIndex]);
        }
    }

    return parameters;
}

const unsigned int Computer::getDestination(const Instruction instruction) {
    unsigned int destination = instruction.getDestination();
    std::vector<signed int> parameters = instruction.getParameters();
    std::vector<MODE> modes = instruction.getModes();

    if(destination < 0) {
        return destination;
    }

    if(modes.back() == MODE::POSITION) {
        return read(destination);
    }

    return destination;
}

void Computer::startUp(void) {
    OPCODE opcode = OPCODE::ERROR;
    std::vector<signed int>::iterator instructionStart = registers_.begin();
    while(instructionStart < registers_.end()
       && opcode != OPCODE::FINISHED) {
        std::cout << "computer registers: " << registers_ << std::endl;
        Instruction instruction = Instruction(&instructionStart,
                                              &registers_);

        std::cout << "\tinstruction: " << instruction << std::endl;

        instructionStart = injestIntcode(instruction);
        opcode = instruction.getOpcode();
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
