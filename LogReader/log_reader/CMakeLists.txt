set (TARGET_NAME logReader)

file (GLOB API_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp
     )

file (GLOB MAIN_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
     )

file (GLOB MAIN_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
     )

# add files to the groups to properly show it in the generated VS solution
source_group("api" FILES ${API_HEADERS})
source_group("src" FILES ${MAIN_SRC})
source_group("include" FILES ${MAIN_HEADERS})

# create Static or DLL lib targets
if (LOG_READER_STATIC)
    add_library (${TARGET_NAME} STATIC ${MAIN_SRC} ${MAIN_HEADERS})
else ()
    add_library (${TARGET_NAME} SHARED ${MAIN_SRC} ${MAIN_HEADERS})
endif (LOG_READER_STATIC)

# add compile definition to ditinguish Log Reader target (used to export DLL symbols in case of DLL implementation)
target_compile_definitions(${TARGET_NAME} PRIVATE -DLOG_READER_IMPL)

# add include directories as public to make them visible for the applications
target_include_directories (${TARGET_NAME} PUBLIC  api
                                           PRIVATE include)

install (TARGETS ${TARGET_NAME} DESTINATION ${LR_INSTALL_DIR})
