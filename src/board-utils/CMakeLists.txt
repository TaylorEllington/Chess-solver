add_library(board-utils STATIC 
    include/board-utils/position.h
    include/board-utils/board-utils.h

    board-utils.cpp
    position.cpp
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

gtest_discover_tests( board-utils-tests)