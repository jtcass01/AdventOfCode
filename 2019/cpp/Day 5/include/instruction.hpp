#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include <vector>

#include "../include/utils.hpp"
#include "../include/mode.hpp"
#include "../include/opcode.hpp"

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

class Instruction {
    public:
        Instruction(std::vector<signed int>::iterator *instructionStart,
                    const std::vector<signed int> registers);

        // Getters
        const unsigned int getOpValue() const;
        const OPCODE getOpcode() const;
        const std::vector<MODE> getModes() const;
        const signed int getParameter(const int parameterIndex) const;
        const std::vector<signed int> getParameters() const;
        const signed int getDestination() const;

        unsigned int size() const;

    private:
        unsigned int getParameterCount();
        unsigned int getDestinationCount();
        OPCODE Instruction::determineOpcode(const unsigned int registerValue);
        std::vector<MODE> determineModes();

        unsigned int opValue;
        OPCODE opcode;
        std::vector<MODE> modes;
        std::vector<signed int> &parameters;
        signed int *destination;
};

std::ostream &operator<<(std::ostream &os, const Instruction instruction) {
    os << "{";

    os << "opValue: " << std::to_string(instruction.getOpValue()) << ", ";

    os << "opcode: " << std::to_string(instruction.getOpcode()) << ", ";

    os << "parameters: " << instruction.getParameters() << ", ";

    os << "destination: " << instruction.getDestination() << ", ";

    os << "}";

    return os;
}

#endif
