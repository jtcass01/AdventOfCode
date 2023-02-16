#include "../include/computer.hpp"

std::ostream &operator<<(std::ostream &os, const OPCODE opcode) {
    os << to_string(opcode);
    return os;
}

std::string to_string(const OPCODE &opcode) {
    std::string result = "";

    switch(opcode) {
        case OPCODE::FINISHED:
            result = "finished";
            break;
        case OPCODE::ADD:
            result = "add";
            break;
        case OPCODE::MULTIPLY:
            result = "multiply";
            break;
        case OPCODE::WRITE:
            result = "write";
            break;
        case OPCODE::READ:
            result = "read";
            break;
        case OPCODE::ERROR:
            result = "error";
            break;
        default:
            throw std::runtime_error("to_string(const OPCODE &opcode) not implemented for given OPCODE");
            break;
    }

    return result;
}

OPCODE getOpcode(long registerValue) {
    OPCODE opCode = OPCODE::ERROR;

    if (registerValue < 100) {
        opCode = static_cast<OPCODE>(registerValue);
    } else {
        std::string stringReprestation = std::to_string(registerValue);
        long opValue = stoi(stringReprestation.substr(stringReprestation.length() - 2));
        opCode = static_cast<OPCODE>(opValue);
    }

    return opCode;
};

std::ostream &operator<<(std::ostream &os, const MODE mode) {
    os << to_string(mode);
    return os;
}

std::string to_string(const MODE &mode) {
    std::string result = "";

    switch(mode) {
        case MODE::PARAMETER:
            result = "finished";
            break;
        case MODE::IMMEDIATE:
            result = "add";
            break;
        default:
            throw std::runtime_error("to_string(const MODE &mode) not implemented for given OPCODE");
            break;
    }

    return result;
}

MODE getMode(long registerValue) {
    MODE mode = MODE::IMMEDIATE;

    if (registerValue > 99) {
        mode = MODE::PARAMETER;
    }

    return mode;
}

std::vector<bool> getParameterModes(const std::vector<unsigned long> instruction) {
    std::string strOp = std::to_string(instruction[0]);

    assert(strOp.size() > 2);

    std::vector<bool> parameterModes(strOp.size() - 2, false);

    for(unsigned long parameterReverseIndex = strOp.size() - 2 - 1,
        parameterIndex = 0;
        parameterIndex >= 0;
        parameterReverseIndex--, parameterIndex++) {
        parameterModes[parameterIndex] = strOp[parameterIndex] == '1';
    }

    return parameterModes;
}


template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> vec) {
    os << "[";
    // Loop through the vector and print each element
    for (long vector_i = 0; vector_i < vec.size(); vector_i++) {
        os << vec[vector_i];

        // Add a comma after each element, except the last one
        if (vector_i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";

    return os;
}

int getInstructionSize(OPCODE opcode) {
    int instructionSize = 0;

    switch(opcode) {
    case OPCODE::FINISHED:
        instructionSize = 1;
        break;
    case OPCODE::ADD:
        instructionSize = 4;
        break;
    case OPCODE::MULTIPLY:
        instructionSize = 4;
        break;
    case OPCODE::WRITE:
        instructionSize = 2;
        break;
    case OPCODE::READ:
        instructionSize = 2;
        break;
    case OPCODE::ERROR:
    default:
        instructionSize = 0;
        break;
    }

    return instructionSize;
}

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

void Computer::setupInstruction(std::vector<unsigned long> *pInstruction) {
    std::vector<unsigned long> instruction = *pInstruction;

    MODE mode = getMode(instruction[0]);

    switch(mode) {
        case MODE::IMMEDIATE:
            instruction[1] = read(instruction[1]);
            instruction[2] = read(instruction[2]);
            break;
        case MODE::PARAMETER:
            std::vector<bool> parameterModes = getParameterModes(instruction);

            for(unsigned int parameterIndex = 0;
                parameterIndex < parameterModes.size();
                parameterIndex++) {
                if(parameterModes[parameterIndex]) {
                    instruction[parameterIndex+1] = read(instruction[parameterIndex+1]);
                }
            }
            break;
    }
}

std::vector<unsigned long> Computer::getInstruction(std::vector<unsigned long>::iterator *instructionStart) {
    long startIndex = std::distance(registers.begin(), *instructionStart);
    OPCODE opcode = getOpcode(registers[startIndex]);
    int instructionSize = getInstructionSize(opcode);
    std::vector<unsigned long> instruction(*instructionStart, *instructionStart+instructionSize);
    std::cout << "Instruction Before Setup: " << instruction << std::endl;
    setupInstruction(&instruction);
    std::cout << "Instruction After Setup: " << instruction << std::endl;
    *instructionStart += instructionSize;
    return instruction;
}

OPCODE Computer::injestIntcode(const std::vector<unsigned long> instruction) {
    assert(instruction.size() > 0);

    OPCODE opcode = static_cast<OPCODE>(instruction[0]);
    int expectedIntructionSize =  getInstructionSize(opcode);
    unsigned long registerOneValue = 0;
    unsigned long registerTwoValue = 0;
    assert(instruction.size() == expectedIntructionSize);

    switch(opcode) {
        case OPCODE::FINISHED:
            std::cout << "STOP OPCODE RECEIVED." << std::endl;
            break;
        case OPCODE::ADD:
            registerOneValue = instruction[1];
            registerTwoValue = instruction[2];
            write(instruction[3], registerOneValue + registerTwoValue);
            break;
        case OPCODE::MULTIPLY:
            registerOneValue = instruction[1];
            registerTwoValue = instruction[2];
            write(instruction[3], registerOneValue * registerTwoValue);
            break;
        case OPCODE::WRITE:
            std::cout << std::to_string(instruction[1]) << " input: ";
            std::cin >> registerOneValue;
            write(instruction[1], registerOneValue);
            break;
        case OPCODE::READ:
            registerOneValue = read(instruction[1]);
            std::cout << std::to_string(instruction[1]) << " output: ";
            std::cout << registerOneValue << std::endl;
            break;
        case OPCODE::ERROR:
        default:
            break;
    }

    return opcode;
}

void Computer::startUp(void) {
    OPCODE opCode = OPCODE::ERROR;
    std::vector<unsigned long>::iterator instructionStart = registers.begin();
    std::cout << "Staring up computer: " << getRegisters() << std::endl;

    while(instructionStart < registers.end()
       && opCode != OPCODE::FINISHED) {
        std::vector<unsigned long> instruction = getInstruction(&instructionStart);
        opCode = injestIntcode(instruction);
        std::cout << "registers state: " << getRegisters() << std::endl;
        std::cout << "\tafter instruction: " << instruction << std::endl;
    }
}

void Computer::write(const unsigned int registerNumber, const unsigned long registerValue) {
  registers[registerNumber] = registerValue;
}

const std::vector<unsigned long> Computer::getRegisters() const {
    return registers;
}

const unsigned long Computer::read(const unsigned int registerNumber) const {
  return registers[registerNumber];
}

std::ostream &operator<<(std::ostream &os, const Computer computer) {
    const std::vector<unsigned long> registers = computer.getRegisters();

    os << "[";
    // Loop through the vector and print each element
    for (unsigned long register_i = 0; register_i < registers.size(); register_i++) {
        os << registers[register_i];

        // Add a comma after each element, except the last one
        if (register_i != registers.size() - 1) {
            os << ", ";
        }
    }
    os << "]";

    return os;
}
