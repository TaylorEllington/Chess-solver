

add_library(sample-lib STATIC
    sample.h
    sample.cpp
)

target_include_directories(sample-lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

add_executable( sample-tests
    tests/sample-tests.cpp
)

target_link_libraries( sample-tests 
    sample-lib 
    GTest::gtest_main
)