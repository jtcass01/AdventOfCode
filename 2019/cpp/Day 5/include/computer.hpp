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

std::ostream &operator<<(std::ostream &os, const OPCODE opcode);

std::string to_string(const OPCODE &opcode);

OPCODE getOpcode(int registerValue);

int getInstructionSize(OPCODE opcode);

enum MODE {
    PARAMETER = 0,
    IMMEDIATE = 1
};

std::ostream &operator<<(std::ostream &os, const MODE mode);

std::string to_string(const MODE &mode);

MODE getMode(int registerValue);

std::vector<bool> getParameterModes(const std::vector<unsigned int> instruction);

class Computer {
    public:
        Computer(const std::string programFile);

        void setupInstruction(std::vector<unsigned int> *pInstruction);

        std::vector<unsigned int> getInstruction(std::vector<unsigned int>::iterator *instructionStart);

        unsigned int read(const int registerNumber);

        void write(const int registerNumber, const unsigned int registerValue);

        void startUp(void);

        const std::vector<unsigned int> getRegisters() const;

    private:
        std::vector<unsigned int> registers;

        OPCODE injestIntcode(const std::vector<unsigned int> instruction);
};

std::ostream &operator<<(std::ostream &os, const Computer computer);

#endif
