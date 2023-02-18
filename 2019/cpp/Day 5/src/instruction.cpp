#include "../include/instruction.hpp"

Instruction::Instruction(std::vector<signed int>::iterator *instructionStart,
                         std::vector<signed int> registers) :
        opValue(registers[std::distance(registers.begin(), *instructionStart)]),
        opcode(determineOpcode(opValue)),
        modes(determineModes()),
        parametersStart(*instructionStart+1),
        parametersEnd(*instructionStart+1+getParameterCount()) {
    unsigned int startIndex = std::distance(registers.begin(), *instructionStart);

    if(getDestinationCount() == 1) {
        destination = &registers[startIndex+size()];
    } else {
        destination = nullptr;
    }
}

unsigned int Instruction::size() const {
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
            errorMessage << "Instruction.size(...) not implemented for given OPCODE: " << opcode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    return instructionSize;
}

const unsigned int Instruction::getOpValue() const {
    return opValue;
}

const OPCODE Instruction::getOpcode() const {
    return opcode;
}

const std::vector<MODE> Instruction::getModes() const {
    return modes;
}

const signed int Instruction::getParameter(const int parameterIndex) const {
    const std::vector<signed int> parameters = getParameters();
    return parameters[parameterIndex];
}

const std::vector<signed int> Instruction::getParameters() const {
    return std::vector<signed int>(parametersStart, parametersEnd);
}

const signed int Instruction::getDestination() const {
    if (destination == nullptr) {
        return -1;
    } else {
        return *destination;
    }
}

unsigned int Instruction::getParameterCount() {
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

unsigned int Instruction::getDestinationCount() {
    std::stringstream errorMessage;
    unsigned int destinationSize = 0;

    switch(opcode) {
    case OPCODE::FINISHED:
        destinationSize = 0;
        break;
    case OPCODE::ADD:
        destinationSize = 1;
        break;
    case OPCODE::MULTIPLY:
        destinationSize = 1;
        break;
    case OPCODE::WRITE:
        destinationSize = 1;
        break;
    case OPCODE::READ:
        destinationSize = 1;
        break;
    case OPCODE::ERROR:
    default:
        destinationSize = 0;
        errorMessage << "getInstructionSize(...) not implemented for given OPCODE: " << opcode << std::endl;
        throw std::runtime_error(errorMessage.str());
    }

    return destinationSize;
}

OPCODE Instruction::determineOpcode(const unsigned int registerValue) {
    OPCODE opcode = OPCODE::ERROR;

    if (registerValue < 100) {
        opcode = static_cast<OPCODE>(registerValue);
    } else {
        std::string stringReprestation = std::to_string(registerValue);
        int opValue = stoi(stringReprestation.substr(stringReprestation.length() - 2));
        opcode = static_cast<OPCODE>(opValue);
    }

    return opcode;
};

std::vector<MODE> Instruction::determineModes() {
    std::string strOp = std::to_string(opValue);
    std::vector<MODE> parameterModes(size(), MODE::POSITION);

    if (opValue > 99) {
        for(unsigned int parameterReverseIndex = strOp.size() - 2 - 1,
            parameterIndex = 0;
            parameterIndex >= 0;
            parameterReverseIndex--, parameterIndex++) {
            if (strOp[parameterReverseIndex] == '1') {
                parameterModes[parameterIndex] = MODE::IMMEDIATE;
            }
        }
    }

    return parameterModes;
}
