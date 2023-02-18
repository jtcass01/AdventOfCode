#ifndef __OPCODE_H_
#define __OPCODE_H_

#include <iostream>
#include <sstream>

enum OPCODE {
    FINISHED = 99,
    ADD = 1,
    MULTIPLY = 2,
    WRITE = 3,
    READ = 4,
    ERROR = 0
};

inline std::string to_string(const OPCODE &opcode) {
    std::stringstream errorMessage;
    std::string result = "";

    switch(opcode) {
        case OPCODE::FINISHED:
            result = "finished";
            break;
        case OPCODE::ADD:
            result = "add";
            break;
        case OPCODE::MULTIPLY:
            result = "multiply";
            break;
        case OPCODE::WRITE:
            result = "write";
            break;
        case OPCODE::READ:
            result = "read";
            break;
        case OPCODE::ERROR:
            result = "error";
            break;
        default:
            errorMessage << "to_string(const OPCODE &opcode) not implemented for given OPCODE:" << opcode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    return result;
}

inline std::ostream &operator<<(std::ostream &os, const OPCODE opcode) {
    os << to_string(opcode);
    return os;
}

#endif
