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
    JUMP_IF_TRUE = 5,
    JUMP_IF_FALSE = 6,
    LESS_THAN = 7,
    EQUALS = 8,
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
        case OPCODE::JUMP_IF_TRUE:
            result = "jump-if-true";
            break;
        case OPCODE::JUMP_IF_FALSE:
            result = "jump-if-false";
            break;
        case OPCODE::LESS_THAN:
            result = "less than";
            break;
        case OPCODE::EQUALS:
            result = "equals";
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

inline unsigned int getParameterCount(const OPCODE opcode) {
    std::stringstream errorMessage;
    int parameterSize = 0;

    switch(opcode) {
    case OPCODE::FINISHED:
        parameterSize = 0;
        break;
    case OPCODE::ADD:
        parameterSize = 2;
        break;
    case OPCODE::MULTIPLY:
        parameterSize = 2;
        break;
    case OPCODE::WRITE:
        parameterSize = 0;
        break;
    case OPCODE::READ:
        parameterSize = 1;
        break;
    case OPCODE::JUMP_IF_TRUE:
        parameterSize = 2;
        break;
    case OPCODE::JUMP_IF_FALSE:
        parameterSize = 2;
        break;
    case OPCODE::LESS_THAN:
        parameterSize = 2;
        break;
    case OPCODE::EQUALS:
        parameterSize = 2;
        break;
    case OPCODE::ERROR:
    default:
        parameterSize = 0;
        errorMessage << "getParameterCount(OPCODE opcode) not implemented for given OPCODE: " << opcode << std::endl;
        throw std::runtime_error(errorMessage.str());
    }

    return parameterSize;
}

inline unsigned int getDestinationCount(const OPCODE opcode) {
    std::stringstream errorMessage;
    unsigned int destinationSize = 0;

    switch(opcode) {
    case OPCODE::FINISHED:
        destinationSize = 0;
        break;
    case OPCODE::ADD:
        destinationSize = 1;
        break;
    case OPCODE::MULTIPLY:
        destinationSize = 1;
        break;
    case OPCODE::WRITE:
        destinationSize = 1;
        break;
    case OPCODE::READ:
        destinationSize = 0;
        break;
    case OPCODE::JUMP_IF_TRUE:
        destinationSize = 0;
        break;
    case OPCODE::JUMP_IF_FALSE:
        destinationSize = 0;
        break;
    case OPCODE::LESS_THAN:
        destinationSize = 1;
        break;
    case OPCODE::EQUALS:
        destinationSize = 1;
        break;
    case OPCODE::ERROR:
    default:
        destinationSize = 0;
        errorMessage << "getDestinationCount(OPCODE opcode) not implemented for given OPCODE: " << opcode << std::endl;
        throw std::runtime_error(errorMessage.str());
    }

    return destinationSize;
}

#endif
