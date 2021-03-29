#include <string.h>
#include <stdlib.h>
#include "lr_filter.hpp"
#include "lr_utils.hpp"

namespace Filter {
    static bool checkFilterMask(const char* maskPtr, const char* linePtr, size_t maskLen) {
        size_t i = 0;
        while (i < maskLen) {
            if (*linePtr == '\0') return false;
            if ((*maskPtr != '?') && (*maskPtr != *linePtr)) return false;
            maskPtr++; linePtr++;
            i++;
        }
        return true;
    }

    bool isInLine(const char* filter, const char* line) {
        if (!filter) {
            printf("\t\tFilter::Checker::isInLine(), wrong filter (NULL) is passed!\n");
            return false;
        }

        size_t lineLen = strlen(line);
        size_t filterLen = strlen(filter);

        const char* filterPtr = filter;
        const char* linePtr = line;

        bool skipAny = false;  /* means "*" symbol was met and any number of symbols can be skipped */
        bool found = false;

        while (*filterPtr != '\0') {
            if (*filterPtr == '*') {
                /* just skip it and read next symbol from the filter */
                filterPtr++;
                skipAny = true;
            }
            else {
                /* all other symbols from the filter are treated as substring mask patterns */

                /* read current filter mask */
                const char* tmpPtr = filterPtr;
                while (*tmpPtr != '*' && *tmpPtr != '\0') {
                    tmpPtr++;
                }
                size_t maskLen = tmpPtr - filterPtr;

                /* if the filter ends with this masks, e.g. the filter is "*ab?d" */
                bool endFilter = (filterPtr + maskLen == filter + filterLen);

                found = false;
                if (skipAny) {
                    if (endFilter) {
                        /* if the line should be ended with this mask */
                        linePtr = line + lineLen - maskLen;
                        return checkFilterMask(filterPtr, linePtr, maskLen);
                    }

                    /* we search first substring within the line
                       which matches current filter mask */
                    while ((linePtr - line) + maskLen <= lineLen) {
                        if (checkFilterMask(filterPtr, linePtr, maskLen)) {
                            found = true;
                            break;
                        }
                        linePtr++;
                    }
                    if (!found) return false;
                    filterPtr += maskLen;
                    skipAny = false;
                }
                else {
                    if (!checkFilterMask(filterPtr, linePtr, maskLen)) {
                        return false;
                    }
                    filterPtr += maskLen;
                    linePtr += maskLen;
                    if (endFilter) {
                        /* if it's last filter mask then the line should not contain any other symbols */
                        return (linePtr == line + lineLen);
                    }
                }
            }
        }
        return true;
    }
}  // namespace Filter
