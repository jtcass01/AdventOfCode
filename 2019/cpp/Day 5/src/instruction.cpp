#include "../include/instruction.hpp"

Instruction::Instruction(std::vector<signed int>::iterator *instructionStart,
                         std::vector<signed int> *registers) :
        opValue_((*registers)[std::distance(registers->begin(), *instructionStart)]),
        opcode_(determineOpcode(opValue_)),
        modes_(determineModes()),
        parametersStart_(*instructionStart+1),
        parametersStop_(*instructionStart+1+getParameterCount(opcode_)) {
    unsigned int startIndex = std::distance(registers->begin(), *instructionStart);

    if(getDestinationCount(opcode_) == 1) {
        destination_ = &(*registers)[startIndex+size()-1];
    } else {
        destination_ = nullptr;
    }
}

unsigned int Instruction::size() const {
    unsigned int instructionSize = getParameterCount(opcode_)+getDestinationCount(opcode_)+1;

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

const std::vector<signed int>::iterator Instruction::getParametersStart() const {
    return parametersStart_;
}

const std::vector<signed int>::iterator Instruction::getParametersStop() const {
    return parametersStop_;
}

const std::vector<signed int> Instruction::getParameters() const {
    return std::vector<signed int>(parametersStart_, parametersStop_);
}

const signed int Instruction::getDestination() const {
    if (destination_ == nullptr) {
        return -1;
    } else {
        return *destination_;
    }
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
    std::vector<MODE> parameterModes(size()-1, MODE::POSITION);

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

    return parameterModes;
}

std::ostream &operator<<(std::ostream &os, const Instruction instruction) {
    os << "{";

    os << "opValue_: " << std::to_string(instruction.getOpValue()) << ", ";

    os << "opcode_: " << to_string(instruction.getOpcode()) << ", ";

    os << "instructionSize: " << instruction.size() << ", ";

    os << "parameters: " << instruction.getParameters() << ", ";

    os << "modes_: " << instruction.getModes() << ", ";

    os << "destination_: " << instruction.getDestination() << "}";

    return os;
}
