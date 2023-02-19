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
    signed int result = 0;
    std::vector<signed int> instructionParameters = getInstructionParameters(instruction);

    switch(opcode) {
        case OPCODE::FINISHED:
            std::cout << "STOP OPCODE RECEIVED." << std::endl;
            return registers_.end();
        case OPCODE::ADD:
            result = sum<signed int>(instructionParameters);
            write(instruction.getDestination(), result);
            break;
        case OPCODE::MULTIPLY:
            result = product<signed int>(instructionParameters);
            write(instruction.getDestination(), result);
            break;
        case OPCODE::WRITE:
            std::cout << std::to_string(instruction.getDestination()) << " input: ";
            std::cin >> result;
            write(instruction.getDestination(), result);
            break;
        case OPCODE::READ:
            result = instructionParameters[0];
            std::cout << std::to_string(instructionParameters[0]) << " output: ";
            std::cout << result << std::endl;
            break;
        case OPCODE::JUMP_IF_TRUE:
            result = instructionParameters[0];

            if (result != 0) {
                return registers_.begin() + instructionParameters[1];
            }

            break;
        case OPCODE::JUMP_IF_FALSE:
            result = instructionParameters[0];

            if (result == 0) {
                return registers_.begin() + instructionParameters[1];
            }

            break;
        case OPCODE::LESS_THAN:
            if(instructionParameters[0] < instructionParameters[1]) {
                write(instruction.getDestination(), 1);
            } else {
                write(instruction.getDestination(), 0);
            }
            break;
        case OPCODE::EQUALS:
            if(instructionParameters[0] == instructionParameters[1]) {
                write(instruction.getDestination(), 1);
            } else {
                write(instruction.getDestination(), 0);
            }
            break;
        case OPCODE::ERROR:
        default:
            errorMessage << "Computer::injestIntcode(...) not implemented for given OPCODE: " << opcode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    std::cout << "hmmm" << std::endl;
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

        instructionStart = injestIntcode(instruction);
        opcode = instruction.getOpcode();

        std::cout << "\topcode: " << opcode << std::endl;
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
