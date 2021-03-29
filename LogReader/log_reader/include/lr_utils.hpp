#pragma once
#include <stdio.h>

#define RELEASE(ptr) \
    if (ptr) {       \
        delete(ptr);   \
        ptr = NULL;  \
    }

namespace Utils {
    static const size_t INITIAL_READLINE_LEN = 64;

    char* strdup(const char* src);

    bool readline(char*& readLineBuf, size_t& readLineBufAllocSize, size_t& readLen, FILE* file);
}  // namespace Utils
