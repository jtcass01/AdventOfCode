#include "../include/computer.hpp"


template <typename T>
T sum(const std::vector<T> values) {
    T result = 0;

    for (T value : values) {
        result += value;
    }

    return result;
}

template <typename T>
T product(const std::vector<T> values) {
    T result = 1;

    for (T value : values) {
        result *= value;
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const OPCODE opcode) {
    os << to_string(opcode);
    return os;
}

std::string to_string(const OPCODE &opcode) {
    std::stringstream errorMessage;
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
            errorMessage << "to_string(const OPCODE &opcode) not implemented for given OPCODE:" << opcode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    return result;
}

OPCODE getOpcode(int registerValue) {
    assert(registerValue > 0);
    OPCODE opCode = OPCODE::ERROR;

    if (registerValue < 100) {
        opCode = static_cast<OPCODE>(registerValue);
    } else {
        std::string stringReprestation = std::to_string(registerValue);
        int opValue = stoi(stringReprestation.substr(stringReprestation.length() - 2));
        opCode = static_cast<OPCODE>(opValue);
    }

    return opCode;
};

std::ostream &operator<<(std::ostream &os, const MODE mode) {
    os << to_string(mode);
    return os;
}

std::string to_string(const MODE &mode) {
    std::stringstream errorMessage;
    std::string result = "";

    switch(mode) {
        case MODE::POSITION:
            result = "position";
            break;
        case MODE::IMMEDIATE:
            result = "immediate";
            break;
        default:
            errorMessage << "to_string(const MODE &mode) not implemented for given MODE: " << mode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    return result;
}

MODE getMode(int registerValue) {
    assert(registerValue > 0);

    MODE mode = MODE::POSITION;

    if (registerValue > 99) {
        mode = MODE::IMMEDIATE;
    }

    return mode;
}

std::vector<MODE> getParameterModes(const std::vector<signed int> instruction,
                                    const OPCODE opcode) {
    std::string strOp = std::to_string(instruction[0]);
    unsigned int instructionSize = getInstructionSize(opcode);
    std::vector<MODE> parameterModes(instructionSize, MODE::POSITION);

    if (instruction[0] > 99) {
        for(unsigned int parameterReverseIndex = strOp.size() - 2 - 1,
            parameterIndex = 0;
            parameterIndex >= 0;
            parameterReverseIndex--, parameterIndex++) {
            if (strOp[parameterReverseIndex] == '1') {
                parameterModes[parameterIndex] = strOp[parameterIndex] == MODE::IMMEDIATE;
            }
        }
    }

    std::cout << "Parameter modes for " << instruction << " are " << parameterModes << std::endl;

    return parameterModes;
}


template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> vec) {
    os << "[";
    // Loop through the vector and print each element
    for (unsigned int vector_i = 0; vector_i < vec.size(); vector_i++) {
        os << vec[vector_i];

        // Add a comma after each element, except the last one
        if (vector_i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";

    return os;
}

unsigned int getInstructionSize(const OPCODE opcode) {
    std::stringstream errorMessage;
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
        errorMessage << "getInstructionSize(...) not implemented for given OPCODE: " << opcode << std::endl;
        throw std::runtime_error(errorMessage.str());
    }

    return instructionSize;
}

unsigned int getParameterCount(const OPCODE opcode) {
    std::stringstream errorMessage;
    int parameterSize = 0;

    switch(opcode) {
    case OPCODE::FINISHED:
        parameterSize = 0;
        break;
    case OPCODE::ADD:
        parameterSize = 2;
        break;
    case OPCODE::MULTIPLY:
        parameterSize = 2;
        break;
    case OPCODE::WRITE:
        parameterSize = 1;
        break;
    case OPCODE::READ:
        parameterSize = 1;
        break;
    case OPCODE::ERROR:
    default:
        parameterSize = 0;
        errorMessage << "getInstructionSize(...) not implemented for given OPCODE: " << opcode << std::endl;
        throw std::runtime_error(errorMessage.str());
    }

    return parameterSize;
}

std::vector<signed int> getParameterValues(const std::vector<signed int> instruction,
                                           const std::vector<MODE> parameterModes,
                                           const OPCODE opcode) {
    std::vector<signed int> parameterValues;

    unsigned int parameterCount = getParameterCount(opcode);
    for(unsigned int parameterValueIndex = 0; parameterValueIndex < parameterCount; parameterValueIndex++) {
        switch(parameterModes[1+parameterValueIndex]) {
            case MODE::IMMEDIATE:
                parameterValues.push_back(instruction[1+parameterValueIndex]);
                break;
            case MODE::POSITION:
                parameterValues.push_back(read(instruction[1+parameterValueIndex]));
                break;
        }
    }

    return parameterValues;
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
    registers_.push_back(stoi(programValue));
  }

  programFile.close();
}

Computer::Computer(std::vector<signed int> registers) : registers_(registers) {}

// void Computer::setupInstruction(std::vector<signed int> *pInstruction) {
//     std::vector<bool> parameterModes;
//     std::stringstream errorMessage;
//     std::vector<signed int> instruction = *pInstruction;

//     MODE mode = getMode(instruction[0]);

//     switch(mode) {
//         case MODE::IMMEDIATE:
//             parameterModes = getParameterModes(instruction);

//             for(signed int parameterIndex = 0;
//                 parameterIndex < parameterModes.size();
//                 parameterIndex++) {
//                 if(parameterModes[parameterIndex]) {
//                     instruction[parameterIndex+1] = read(instruction[parameterIndex+1]);
//                 }
//             }
//             break;
//         case MODE::POSITION:
//             instruction[1] = read(instruction[1]);
//             instruction[2] = read(instruction[2]);
//             break;
//         default:
//             errorMessage << "Computer::setupInstruction(...) not implemented for given MODE: " << mode << std::endl;
//             throw std::runtime_error(errorMessage.str());
//     }
// }

std::vector<signed int> Computer::getInstruction(std::vector<signed int>::iterator *instructionStart) {
    unsigned int startIndex = std::distance(registers_.begin(), *instructionStart);
    OPCODE opcode = getOpcode(registers_[startIndex]);
    unsigned int instructionSize = getInstructionSize(opcode);
    std::vector<signed int> instruction(*instructionStart, *instructionStart+instructionSize);
    // std::cout << opcode << " instruction before setup: " << instruction << std::endl;
    // setupInstruction(&instruction);
    // std::cout << opcode << " instruction after setup: " << instruction << std::endl;
    *instructionStart += instructionSize;
    return instruction;
}

OPCODE Computer::injestIntcode(const std::vector<signed int> instruction) {
    std::stringstream errorMessage;
    assert(instruction.size() > 0);

    OPCODE opcode = static_cast<OPCODE>(instruction[0]);
    std::vector<MODE> parameterModes = getParameterModes();
    unsigned int expectedIntructionSize =  getInstructionSize(opcode);
    signed int result = 0;
    assert(instruction.size() == expectedIntructionSize);

    std::vector<signed int> parameterValues = getParameterValues(instruction,
                                                                 parameterModes,
                                                                 opcode);

    switch(opcode) {
        case OPCODE::FINISHED:
            std::cout << "STOP OPCODE RECEIVED." << std::endl;
            break;
        case OPCODE::ADD:
            result = sum<signed int>(parameterValues);
            write(instruction[3], result);
            break;
        case OPCODE::MULTIPLY:
            result = product<signed int>(parameterValues);
            write(instruction[3], result);
            break;
        case OPCODE::WRITE:
            std::cout << std::to_string(instruction[1]) << " input: ";
            std::cin >> result;
            write(instruction[1], result);
            break;
        case OPCODE::READ:
            result = read(instruction[1]);
            std::cout << std::to_string(instruction[1]) << " output: ";
            std::cout << result << std::endl;
            break;
        case OPCODE::ERROR:
        default:
            errorMessage << "Computer::injestIntcode(...) not implemented for given OPCODE: " << opcode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    return opcode;
}

void Computer::startUp(void) {
    OPCODE opCode = OPCODE::ERROR;
    std::vector<signed int>::iterator instructionStart = registers_.begin();
    std::cout << "Staring up computer: " << getRegisters() << std::endl;

    while(instructionStart < registers_.end()
       && opCode != OPCODE::FINISHED) {
        std::vector<signed int> instruction = getInstruction(&instructionStart);
        opCode = injestIntcode(instruction);
        std::cout << "registers_ state: " << getRegisters() << std::endl;
        std::cout << "\tafter instruction: " << instruction << std::endl;
    }
}

void Computer::write(const unsigned int registerNumber, const signed int registerValue) {
    registers_[registerNumber] = registerValue;
}

const std::vector<signed int> Computer::getRegisters() const {
    return registers_;
}

const signed int Computer::read(const unsigned int registerNumber) const {
  return registers_[registerNumber];
}

std::ostream &operator<<(std::ostream &os, const Computer computer) {
    const std::vector<signed int> registers_ = computer.getRegisters();
    os << registers_;
    return os;
}
