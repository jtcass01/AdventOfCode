#ifndef __COMPUTER_UNITTEST_H_
#define __COMPUTER_UNITTEST_H_

#include "gtest/gtest.h"
#include "computer.hpp"
#include "instruction.hpp"
#include <sstream>
#include <vector>

template <typename T>
inline bool sameVectors(const std::vector<T> a,
                        const std::vector<T> b) {
    bool same = true;

    if(a.size() != b.size()) {
        same = false;
    }

    if (same) {
        for(auto itA = a.begin(),
            itB = b.begin();
            itA != a.end();
            itA++, itB++) {
                if(*itA != *itB) {
                    same = false;
                    break;
                }
            }
    }

    return same;
}

#endif
