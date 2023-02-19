#ifndef __UTILS_H_
#define __UTILS_H_

#include <vector>
#include <iostream>

template <typename T>
T sum(const std::vector<T> values) {
    T result = 0;

    for (T value : values) {
        result += value;
    }

    return result;
}

template <typename T>
T product(const std::vector<T> values) {
    T result = 1;

    for (T value : values) {
        result *= value;
    }

    return result;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> vec) {
    os << "[";
    // Loop through the vector and print each element
    for (unsigned int vector_i = 0; vector_i < vec.size(); vector_i++) {
        os << vec[vector_i];

        // Add a comma after each element, except the last one
        if (vector_i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";

    return os;
}

#endif
