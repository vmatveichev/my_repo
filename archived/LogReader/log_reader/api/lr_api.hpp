/* This is an API header file which is included by a user application */
#pragma once

#if defined(LOG_READER_STATIC)
    #define LOG_READER_API(TYPE) TYPE
#else
    /* export API symbols from the LogReader.dll */
    #if defined (_WIN32)
        #if defined(LOG_READER_IMPL)
            #define  LOG_READER_API(TYPE) __declspec(dllexport) TYPE
        #else
            #define  LOG_READER_API(TYPE) __declspec(dllimport) TYPE
        #endif
    #else
        /* ideally it would be good to use visibility(hidden) to hide
           all other symbols (on Linux all the symbols are opened by default),
           currently not implemented*/
        #define LOG_READER_API(TYPE) TYPE
    #endif
#endif
