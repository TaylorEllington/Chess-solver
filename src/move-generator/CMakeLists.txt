set(SOURCES
include/move-generator/move-generator.h
move-generator.cpp
)

add_library(move-generator STATIC
    ${SOURCES}
) 

target_link_libraries( move-generator
    board-utils
)

target_include_directories(move-generator INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_executable( move-generator-tests
    tests/move-generator-tests.cpp
)

target_link_libraries( move-generator-tests
    move-generator
    gtest_main
    gmock
)


string(REPLACE ${PROJECT_SOURCE_DIR}/ "" FILE_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_FULL_PATH "")
foreach(SOURCE ${SOURCES})

    list(APPEND SOURCE_FULL_PATH ${FILE_PREFIX}/${SOURCE})

endforeach()

list(APPEND SOURCE_FULL_PATH ${SOURCES_FOR_CODE_COVERAGE})
set(SOURCES_FOR_CODE_COVERAGE ${SOURCE_FULL_PATH} PARENT_SCOPE)

gtest_discover_tests( move-generator-tests)
