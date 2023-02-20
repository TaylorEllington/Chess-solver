cmake_minimum_required(VERSION 3.10)
project(Chess-solver VERSION 0.0.0 LANGUAGES CXX)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

option(CODE_COVERAGE "Turns on special behavior for building code coverage versions of binaries, and running the scan" OFF)


if(CODE_COVERAGE)
    # we need gcode and gcc, so lets make sure they are around
    if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(FATAL_ERROR "Must run code coverage builds on gcc, with gcov installed")
    endif()

    find_program(GCOV_BIN gcov)
    if(NOT gcov_FOUND)
        message(FATAL_ERROR "Must run code coverage builds on platform with gcov installed")
    endif()

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

# Add third-party libraries
# add_subdirectory(third-party)

# Add project source code
add_subdirectory(src)