SET(LR_INSTALL_DIR ${CMAKE_SOURCE_DIR}/install)
SET(LR_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

# set paths to the output binaries
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LR_BINARY_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LR_BINARY_DIR})
if (MSVC)
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LR_BINARY_DIR})
else ()
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LR_BINARY_DIR}/lib)
endif ()

# enable all warnings to be checked and treat each detected warning as error
if (MSVC)
    add_compile_options("/W4" "/WX")
else ()
    add_compile_options("-Wall" "-Werror")
endif ()

# add compile option for all targets in case of static linking
if (LOG_READER_STATIC)
    add_definitions(-DLOG_READER_STATIC)
endif (LOG_READER_STATIC)
