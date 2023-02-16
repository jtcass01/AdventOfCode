#ifndef __COMPUTER_H_
#define __COMPUTER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>

enum OPCODE {
    FINISHED = 99,
    ADD = 1,
    MULTIPLY = 2,
    WRITE = 3,
    READ = 4,
    ERROR = 0
};

OPCODE getOpcode(int registerValue);

int getInstructionSize(OPCODE opcode);

enum MODE {
    PARAMETER = 0,
    IMMEDIATE = 1
};

MODE getMode(int registerValue);

std::vector<bool> getParameterModes(const std::vector<double> instruction);

class Computer {
    public:
        Computer(const std::string programFile);

        void setupInstruction(std::vector<double> *pInstruction);

        std::vector<double> getInstruction(std::vector<double>::iterator *instructionStart);

        double read(const int registerNumber);

        void write(const int registerNumber, const double registerValue);

        void startUp(void);

        const std::vector<double> getRegisters() const;

    private:
        std::vector<double> registers;

        OPCODE injestIntcode(const std::vector<double> instruction);
};

std::ostream &operator<<(std::ostream &os, const Computer computer);

#endif
