set ("${PROJECT}_BINARY_DIR"  bin)
set ("${PROJECT}_SOURCE_DIR" src:include)
set ("${PROJECT}_LIB_DIR" lib)

set (CMAKE_INCLUDE_PATH ${${PROJECT}_SOURCE_DIR})
set (CMAKE_LIBRARY_PATH ${${PROJECT}_LIB_DIR})
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_BINARY_DIR})
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_BUILD_TYPE Debug)

set (ERR_NO_UNIX "Cannot build on non Unix systems")

if ( WITH_DEBUG_MODE )
     ADD_DEFINITIONS( -DMY_DEBUG_MODE=1)
endif()

if ( CMAKE_COMPILER_IS_GNUCXX )
    set(MY_CXX_FLAGS  "-Wall -std=c++14 -fmessage-length=0 -v")
    set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS}")
else ()
    message (FATAL_ERROR ${ERR_NO_UNIX})
endif ()
