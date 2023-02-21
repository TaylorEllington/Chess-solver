cmake_minimum_required(VERSION 3.10)
project(Chess-solver VERSION 0.0.0 LANGUAGES CXX)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

option(CODE_COVERAGE "Turns on special behavior for building code coverage versions of binaries, and running the scan" OFF)


if(CODE_COVERAGE)
    # we need gcode and gcc, so lets make sure they are around
    if( NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # message(FATAL_ERROR "Must run code coverage builds on gcc, with gcov installed")
    endif()

    find_program(GCOV_BIN gcov)

    if(NOT GCOV_BIN)
        # message(FATAL_ERROR "Must run code coverage builds on platform with gcov installed")
    endif()

    # turn on compile flags needed for gcov
    SET(GCC_COVERAGE_COMPILE_FLAGS "-coverage -fprofile-arcs -ftest-coverage -fPIC -O0")
    SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

    # Create OBJECT_DIR variable
    set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/chess-solver.dir)
    message("-- Object files will be output to: ${OBJECT_DIR}")

endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# Add project source code


add_subdirectory(src)
