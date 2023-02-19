#include "../include/instruction.hpp"

Instruction::Instruction(std::vector<signed int>::iterator *instructionStart,
                         std::vector<signed int> registers) :
        opValue_(registers[std::distance(registers.begin(), *instructionStart)]),
        opcode_(determineOpcode(opValue_)),
        modes_(determineModes()),
        parametersStart_(*instructionStart+1),
        parametersEnd_(*instructionStart+1+getParameterCount()) {
    unsigned int startIndex = std::distance(registers.begin(), *instructionStart);
    std::cout << "startIndex:" << startIndex << std::endl;

    if(getDestinationCount() == 1) {
        destination_ = &registers[startIndex+size()];
    } else {
        destination_ = nullptr;
    }
    std::cout << "destination_:" << getDestination() << std::endl;
}

unsigned int Instruction::size() const {
    std::stringstream errorMessage;
    int instructionSize = 0;

    switch(opcode_) {
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
            errorMessage << "Instruction.size() not implemented for given OPCODE: " << opcode_ << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    return instructionSize;
}

const unsigned int Instruction::getOpValue() const {
    return opValue_;
}

const OPCODE Instruction::getOpcode() const {
    return opcode_;
}

const std::vector<MODE> Instruction::getModes() const {
    return modes_;
}

const signed int Instruction::getParameter(const int parameterIndex) const {
    const std::vector<signed int> parameters = getParameters();
    return parameters[parameterIndex];
}

const std::vector<signed int> Instruction::getParameters() const {
    return std::vector<signed int>(parametersStart_, parametersEnd_);
}

const signed int Instruction::getDestination() const {
    if (destination_ == nullptr) {
        return -1;
    } else {
        return *destination_;
    }
}

unsigned int Instruction::getParameterCount() {
    std::stringstream errorMessage;
    int parameterSize = 0;

    switch(opcode_) {
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
        errorMessage << "Instruction::getParameterCount() not implemented for given OPCODE: " << opcode_ << std::endl;
        throw std::runtime_error(errorMessage.str());
    }

    return parameterSize;
}

unsigned int Instruction::getDestinationCount() {
    std::stringstream errorMessage;
    unsigned int destinationSize = 0;

    switch(opcode_) {
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
        errorMessage << "Instruction::getDestinationCount() not implemented for given OPCODE: " << opcode_ << std::endl;
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
    std::string strOp = std::to_string(opValue_);
    std::vector<MODE> parameterModes(size(), MODE::POSITION);

    if (opValue_ > 99) {
        std::string parameterValuesStr = strOp.substr(0, strOp.size()-2);

        for(int parameterReverseIndex = parameterValuesStr.size() - 1,
            parameterIndex = 0;
            parameterReverseIndex >= 0;
            parameterReverseIndex--, parameterIndex++) {
            if (parameterValuesStr[parameterReverseIndex] == '1') {
                parameterModes[parameterIndex] = MODE::IMMEDIATE;
            }
        }
    }

    std::cout << "parameterModes: " << parameterModes << std::endl;

    return parameterModes;
}

std::ostream &operator<<(std::ostream &os, const Instruction instruction) {
    os << "{";

    os << "opValue_: " << std::to_string(instruction.getOpValue()) << ", ";

    os << "opcode_: " << to_string(instruction.getOpcode()) << ", ";

    os << "parameters: " << instruction.getParameters() << ", ";

    os << "destination_: " << instruction.getDestination() << "}";

    return os;
}
