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
#include <sstream>
#include <exception>

template <typename T>
T sum(std::vector<T> values);

template <typename T>
T product(std::vector<T> values);

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

unsigned int getParameterCount(const OPCODE opcode);

enum MODE {
    POSITION = 0,
    IMMEDIATE = 1
};

std::ostream &operator<<(std::ostream &os, const MODE mode);

std::string to_string(const MODE &mode);

MODE getMode(int registerValue);

std::vector<MODE> getParameterModes(const std::vector<signed int> instruction,
                                    const OPCODE opcode);

std::vector<signed int> getParameterValues(const std::vector<signed int> instruction,
                                           const std::vector<MODE> parameterModes,
                                           const OPCODE opcode);

class Computer {
    public:
        Computer(const std::string programFile);
        Computer(std::vector<signed int> registers);

        // void setupInstruction(std::vector<signed int> *pInstruction);

        std::vector<signed int> getInstruction(std::vector<signed int>::iterator *instructionStart);

        void write(const unsigned int registerNumber, const signed int registerValue);

        void startUp(void);

        const signed int read(const unsigned int registerNumber) const;

        const std::vector<signed int> getRegisters() const;

        const std::vector<signed int> getParameterValues(const std::vector<signed int> instruction,
                                                         const std::vector<MODE> parameterModes,
                                                         const OPCODE opcode);

    private:
        std::vector<signed int> registers_;

        OPCODE injestIntcode(const std::vector<signed int> instruction);
};

std::ostream &operator<<(std::ostream &os, const Computer computer);

#endif
