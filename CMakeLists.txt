cmake_minimum_required(VERSION 3.10)
project(Chess-solver VERSION 0.0.0 LANGUAGES CXX)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

include(BuildOptions.cmake)

if(GCC_STATIC_ANALYSIS)
    SET(GCC_STATIC_ANALYSIS_FLAGS "-fanalyzer")
endif()


if(GCC_CODE_COVERAGE)
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

    add_custom_target(
        code-cov-report
        #OUTPUT "code_coverage_report/index.html"
        COMMAND gcov -b -r -s ${PROJECT_SOURCE_DIR} src/chess-lib-tests.cpp -o ${PROJECT_BINARY_DIR}/src/CMakeFiles/chess-lib-tests.dir/
        COMMAND lcov -c  --directory ${PROJECT_SOURCE_DIR} 
            --output-file unfiltered.info 
            --rc lcov_branch_coverage=1 --no-external
        COMMAND lcov -r unfiltered.info 
            '${PROJECT_BINARY_DIR}/_deps/googletest-src/googletest/*' 
            '${PROJECT_BINARY_DIR}/_deps/googletest-src/googlemock/include/gmock/*' 
            '${PROJECT_SOURCE_DIR}/src/chess-lib-tests.cpp'  
            -o filtered.info 
            --rc lcov_branch_coverage=1
        COMMAND genhtml filtered.info  
            --output-directory code_coverage_report
            --rc genhtml_branch_coverage=1
     )

endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# FetchContent_Declare(
#     cppcheck
#     DOWNLOAD_EXTRACT_TIMESTAMP
#     URL  https://github.com/danmar/cppcheck/archive/refs/tags/2.10.zip
# )

include(ExternalProject)
ExternalProject_Add(
    cppcheck
    EXCLUDE_FROM_ALL true
    URL  https://github.com/danmar/cppcheck/archive/refs/tags/2.10.zip
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/_staticscanner
    INSTALL_COMMAND ${CMAKE_COMMAND} --install ${PROJECT_BINARY_DIR}/cppcheck-prefix/src/cppcheck-build --prefix ${PROJECT_SOURCE_DIR}/_staticscanner --config $<CONFIG> --component applications
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEMP ${CMAKE_SOURCE_DIR})
# set(CMAKE_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/cppcheck-src/" )
# FetchContent_MakeAvailable(cppcheck)

# set(CMAKE_SOURCE_DIR ${TEMP})

enable_testing()
include(GoogleTest)

# Add project source code


add_subdirectory(src)
