cmake_minimum_required (VERSION 3.2)

project(LogReader)

# Log Reader is compiled as DLL by default.
option (LOG_READER_STATIC "Link LogReader as static library" OFF)

# include common file with common CMake variables and flags
list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (common)

# add each target to the build
add_subdirectory (log_reader)
# build tests for the log reader
add_subdirectory (test)
# build samples for the log reader
add_subdirectory (sample)
