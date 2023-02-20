add_library(move-generator STATIC
    include/move-generator/move-generator.h
    move-generator.cpp
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

gtest_discover_tests( move-generator-tests)
