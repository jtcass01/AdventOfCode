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

OPCODE getOpcode(long registerValue);

int getInstructionSize(OPCODE opcode);

enum MODE {
    PARAMETER = 0,
    IMMEDIATE = 1
};

std::ostream &operator<<(std::ostream &os, const MODE mode);

std::string to_string(const MODE &mode);

MODE getMode(long registerValue);

std::vector<bool> getParameterModes(const std::vector<unsigned long> instruction);

class Computer {
    public:
        Computer(const std::string programFile);

        void setupInstruction(std::vector<unsigned long> *pInstruction);

        std::vector<unsigned long> getInstruction(std::vector<unsigned long>::iterator *instructionStart);

        void write(const unsigned int registerNumber, const unsigned long registerValue);

        void startUp(void);

        const unsigned long read(const unsigned int registerNumber) const;

        const std::vector<unsigned long> getRegisters() const;

    private:
        std::vector<unsigned long> registers;

        OPCODE injestIntcode(const std::vector<unsigned long> instruction);
};

std::ostream &operator<<(std::ostream &os, const Computer computer);

#endif
