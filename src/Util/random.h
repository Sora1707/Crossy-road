#pragma once
#include <cstdlib> 

namespace util {
    inline int random(int low, int high) {
        return (rand() % (high - low + 1)) + low;
    }
}

