set (TARGET_NAME log_reader_sample)

file (GLOB MAIN_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
     )

file (GLOB MAIN_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
     )

# add files to the groups to properly show it in the generated VS solution
source_group("src" FILES ${MAIN_SRC})
source_group("include" FILES ${MAIN_HEADERS})

# create EXE target
add_executable (${TARGET_NAME} ${MAIN_SRC} ${MAIN_HEADERS})

# link Log Reader library
target_link_libraries (${TARGET_NAME} logReader)

install (TARGETS ${TARGET_NAME} DESTINATION ${LR_INSTALL_DIR})