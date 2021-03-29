/* this define is added to avoid warning about fopen_s on Windows.
   I can implement using of fopen_s for Windows but it's not clear
   if it will be supported for Win XP from the box (like it's required
   according to the excercise description). So, I have decided to
   easily disable this warning. I hope it's enough for this excersize */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log_reader.hpp"
#include "lr_utils.hpp"
#include "lr_filter.hpp"

CLogReader::CLogReader(const char* fileName) {
    /* here we allocate required memory and copy the pointer
       data to make sure it's not freed unexpectedly by a user */
    _fName = Utils::strdup(fileName);
    if (_fName) {
        printf("\tCLogReader::CLogReader(), internal file name initialized: %s\n", _fName);
    }
    else {
        printf("\tCLogReader::CLogReader(), invalid filename: %s!\n", fileName);
    }

    _lineBufAllocSize = Utils::INITIAL_READLINE_LEN;
    _lineBuf = new char[_lineBufAllocSize];
    if (_lineBuf) {
        printf("\tCLogReader::CLogReader(), line buffer allocated successfully\n");
        memset(_lineBuf, 0, _lineBufAllocSize);
    }
    else {
        printf("\tCLogReader::CLogReader(), line buffer could NOT be allocated\n");
    }
    _readLen = 0;
}

CLogReader::~CLogReader() {
    if (_fd) {
        Close();
    }
    RELEASE(_fName);
    RELEASE(_filter);
    RELEASE(_lineBuf);
}

bool CLogReader::Open() {
    if (!_fName) {
        printf("\tCLogReader::Open(), can't open file with empty name!\n");
        return false;
    }

    if (_fd) {
        printf("\tCLogReader::Open(), LogReader already opened a file!\n");
        return false;
    }

    _fd = fopen(_fName, "r");
    if (!_fd) {
        printf("\tCLogReader::Open(), can't open file!\n");
        return false;
    }

    printf("\tCLogReader::Open(), the file %s is sussesfully opened for reading.\n", _fName);
    return true;
}

void CLogReader::Close() {
    if (_fd) {
        fclose(_fd);
        _fd = NULL;
        printf("\tCLogReader::Close(), the file %s is closed.\n", _fName);
    }
}

bool CLogReader::SetFilter(const char* filter) {
    /* clean up previous filter if it was set */
    RELEASE(_filter);
    _filter = Utils::strdup(filter);
    if (!_filter) {
        printf("\tCLogReader::SetFilter(), can't set filter: %s\n", filter);
        return false;
    }
    printf("\tCLogReader::SetFilter(), filter initialized: %s\n", _filter);

    return true;
}

bool CLogReader::GetNextLine(char* buf, const int bufsize) {
    if (!_fd) {
        printf("\tCLogReader::GetNextLine(), the file %s was not opened!\n", _fName);
        return false;
    }

    if (!_filter) {
        printf("\tCLogReader::GetNextLine(), the filter was not set!\n");
        return false;
    }

    while (Utils::readline(_lineBuf, _lineBufAllocSize, _readLen, _fd)) {
        if (Filter::isInLine(_filter, _lineBuf)) {
            if (_readLen >= static_cast<size_t>(bufsize)) {
                /* if read line is longer than the size of the preallocated user's buffer */
                /* to truncate read line and put it to the buffer */
                memcpy(buf, _lineBuf, bufsize);
                buf[bufsize - 1] = '\0';
            }
            else {
                /* if read line is shorter than the size of the preallocated user's buffer */
                /* just put the read line to the buffer */
                memcpy(buf, _lineBuf, _readLen);
                buf[_readLen] = '\0';
            }
            return true;
        }
    }
    printf("\tCLogReader::GetNextLine(), can't read next line\n");
    return false;
}
