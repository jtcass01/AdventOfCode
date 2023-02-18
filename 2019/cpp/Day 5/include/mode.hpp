#ifndef __MODE_H_
#define __MODE_H_

#include <iostream>
#include <sstream>

enum MODE {
    POSITION = 0,
    IMMEDIATE = 1
};

std::ostream &operator<<(std::ostream &os, const MODE mode) {
    os << to_string(mode);
    return os;
}

std::string to_string(const MODE &mode) {
    std::stringstream errorMessage;
    std::string result = "";

    switch(mode) {
        case MODE::POSITION:
            result = "position";
            break;
        case MODE::IMMEDIATE:
            result = "immediate";
            break;
        default:
            errorMessage << "to_string(const MODE &mode) not implemented for given MODE: " << mode << std::endl;
            throw std::runtime_error(errorMessage.str());
    }

    return result;
}

#endif
