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

#include "../include/utils.hpp"
#include "../include/mode.hpp"
#include "../include/opcode.hpp"
#include "../include/instruction.hpp"


class Computer {
    public:
        Computer(const std::string programFile);
        Computer(std::vector<signed int> registers);

        void write(const unsigned int registerNumber, const signed int registerValue);

        const signed int read(const unsigned int registerNumber) const;

        void startUp(void);

        const std::vector<signed int> getRegisters() const;

    private:
        std::vector<signed int> registers_;

        OPCODE injestIntcode(const Instruction instruction);
};

std::ostream &operator<<(std::ostream &os, const Computer computer);

#endif
