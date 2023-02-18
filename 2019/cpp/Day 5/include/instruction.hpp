#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include <vector>

#include "../include/utils.hpp"
#include "../include/mode.hpp"
#include "../include/opcode.hpp"


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
        OPCODE determineOpcode(const unsigned int registerValue);
        std::vector<MODE> determineModes();

        unsigned int opValue;
        OPCODE opcode;
        std::vector<MODE> modes;
        std::vector<signed int>::iterator parametersStart;
        std::vector<signed int>::iterator parametersEnd;
        signed int *destination;
};

std::ostream &operator<<(std::ostream &os, const Instruction instruction);

#endif
