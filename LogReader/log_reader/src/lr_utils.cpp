#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lr_utils.hpp"

namespace Utils {

    char* strdup(const char* src) {
        /* here we can use strdup func (_strdup on Windows) but
           it's POSIX function and I've decided to implement own one */
        if (!src) return NULL;
        size_t len = strlen(src);
        char* dst = new char[len + 1];
        if (dst) {
            memcpy(dst, src, len);
            dst[len] = '\0';
        }
        else {
            printf("\tUtils::strdup: couldn't allocate required memory.");
        }
        return dst;
    }

    bool readline(char*& lineBuf, size_t& lineBufAllocSize, size_t& readLen, FILE* filePtr) {
        readLen = 0;

        if (!filePtr) {
            printf("\tUtils::readline: file pointer is null.");
            return false;
        }

        if (!lineBuf) {
            printf("\tUtils::readline: line buffer is not allocated!");
            return false;
        }

        int ch = fgetc(filePtr);
        while ((ch != '\n') && (ch != EOF)) {
            if (readLen + 1 >= lineBufAllocSize) {  // use + 1 to always have place for terminating '\0' symbol
                char* tmp = new char[lineBufAllocSize * 2];
                if (!tmp) {
                    printf("\tUtils::readline: line buffer can NOT be reallocated to buf size %u\n", static_cast<int>(lineBufAllocSize * 2));
                    return false;
                }
                memcpy(tmp, lineBuf, strlen(lineBuf));
                lineBufAllocSize *= 2;  // here we extend the buffer up to 2x size
                delete lineBuf;
                lineBuf = tmp;
            }
            lineBuf[readLen] = (char)ch;
            readLen++;

            ch = fgetc(filePtr);
        }

        lineBuf[readLen] = '\0';

        /* we need to distinguish if it's empty line read or EOF */
        if ((readLen == 0) && (ch == EOF)) {
            printf("\t\tUtils::readline: EOF is reached!\n");
            return false;
        }

        return true;
    }
}  // namespace Utils
