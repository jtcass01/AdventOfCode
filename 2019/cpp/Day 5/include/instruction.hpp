#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include <vector>

#include "../include/utils.hpp"
#include "../include/mode.hpp"
#include "../include/opcode.hpp"


class Instruction {
    public:
        Instruction(std::vector<signed int>::iterator *instructionStart,
                    std::vector<signed int> *registers);

        // Getters
        const unsigned int getOpValue() const;
        const OPCODE getOpcode() const;
        const std::vector<MODE> getModes() const;
        const signed int getParameter(const int parameterIndex) const;
        const std::vector<signed int>::iterator getParametersStart() const;
        const std::vector<signed int>::iterator getParametersStop() const;
        const std::vector<signed int> getParameters() const;
        const signed int getDestination() const;

        unsigned int size() const;

    private:
        OPCODE determineOpcode(const unsigned int registerValue);
        std::vector<MODE> determineModes();

        unsigned int opValue_;
        OPCODE opcode_;
        std::vector<MODE> modes_;
        std::vector<signed int>::iterator parametersStart_;
        std::vector<signed int>::iterator parametersStop_;
        signed int *destination_;
};

std::ostream &operator<<(std::ostream &os, const Instruction instruction);

#endif
