#pragma once
#include "lr_api.hpp"

class LOG_READER_API(CLogReader)
{
public:
    CLogReader(const char* fileName);
    ~CLogReader();

    /* Open the file */
    /* returns false in case of an erorr, othervise true*/
    bool Open();

    /* Close the file */
    void Close();

    /* Set regexp filter to be used to find a line */
    /* returns false in case of an erorr, othervise true*/
    bool SetFilter(const char* filter);

    /* Get next line containing pre-set filter*/
    /* returns false in case of an erorr, othervise true*/
    bool GetNextLine(char* buf,
                     const int bufsize);
private:
    char*  _fName     = NULL;  /* file name                                            */
    FILE*  _fd        = NULL;  /* file descriptor of the opened file                   */
    char*  _filter    = NULL;  /* currently used filter                                */

    char*  _lineBuf   = NULL;  /* buffer for read lines                                */
    size_t _lineBufAllocSize;  /* size of the allocated read lines buffer              */
    size_t _readLen;           /* length of the read line currently stored in _lineBuf */
};
