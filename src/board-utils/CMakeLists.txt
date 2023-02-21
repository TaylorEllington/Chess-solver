set(SOURCES
    include/board-utils/position.h
    include/board-utils/board-utils.h
    board-utils.cpp
    position.cpp
)

add_library(board-utils STATIC 
${SOURCES}
)

target_include_directories(board-utils INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)


add_executable( board-utils-tests
    tests/board-utils-tests.cpp
)

target_link_libraries( board-utils-tests
    board-utils
    GTest::gtest_main

)

string(REPLACE ${PROJECT_SOURCE_DIR}/ "" FILE_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_FULL_PATH "")
foreach(SOURCE ${SOURCES})

    list(APPEND SOURCE_FULL_PATH ${FILE_PREFIX}/${SOURCE})

endforeach()

list(APPEND SOURCE_FULL_PATH ${SOURCES_FOR_CODE_COVERAGE})
set(SOURCES_FOR_CODE_COVERAGE ${SOURCE_FULL_PATH} PARENT_SCOPE)

set(SOURCES_FOR_CODE_COVERAGE ${SOURCE_FULL_PATH} PARENT_SCOPE)

gtest_discover_tests( board-utils-tests)