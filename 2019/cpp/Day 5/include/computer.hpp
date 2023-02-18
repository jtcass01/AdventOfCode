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

unsigned int getInstructionSize(const OPCODE opcode);

enum MODE {
    PARAMETER = 0,
    IMMEDIATE = 1
};

std::ostream &operator<<(std::ostream &os, const MODE mode);

std::string to_string(const MODE &mode);

MODE getMode(int registerValue);

std::vector<bool> getParameterModes(const std::vector<signed int> instruction);

class Computer {
    public:
        Computer(const std::string programFile);

        void setupInstruction(std::vector<signed int> *pInstruction);

        std::vector<signed int> getInstruction(std::vector<signed int>::iterator *instructionStart);

        void write(const unsigned int registerNumber, const signed int registerValue);

        void startUp(void);

        const signed int read(const unsigned int registerNumber) const;

        const std::vector<signed int> getRegisters() const;

    private:
        std::vector<signed int> registers;

        OPCODE injestIntcode(const std::vector<signed int> instruction);
};

std::ostream &operator<<(std::ostream &os, const Computer computer);

#endif
