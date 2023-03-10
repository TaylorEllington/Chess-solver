cmake_minimum_required(VERSION 3.10)
project(Chess-solver VERSION 0.0.0 LANGUAGES CXX)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()


option(GCC_CODE_COVERAGE "" ON)


##########################################################################################
## Static Code Scans
##########################################################################################

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(STATIC_SCANNER_CFG_BUILD ${PROJECT_BINARY_DIR}/cppcheck-prefix/src/cppcheck-build/bin/cfg/)
else()
    set(STATIC_SCANNER_CFG_BUILD ${PROJECT_BINARY_DIR}/cppcheck-prefix/src/cppcheck-build/bin/Debug/cfg/)
endif()

include(ExternalProject)
ExternalProject_Add(
    cppcheck
    EXCLUDE_FROM_ALL true
    URL  https://github.com/danmar/cppcheck/archive/refs/tags/2.10.zip
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/_staticscanner
    INSTALL_COMMAND ${CMAKE_COMMAND} 
        --install ${PROJECT_BINARY_DIR}/cppcheck-prefix/src/cppcheck-build 
        --prefix ${PROJECT_SOURCE_DIR}/_staticscanner 
        --config $<CONFIG> --component applications
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${STATIC_SCANNER_CFG_BUILD}     
         ${PROJECT_SOURCE_DIR}/_staticscanner/share/Cppcheck/cfg/
)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(STATIC_SCANNER_EXE ${PROJECT_SOURCE_DIR}/_staticscanner/bin/cppcheck)
else()
    set(STATIC_SCANNER_EXE ${PROJECT_SOURCE_DIR}/_staticscanner/bin/cppcheck.exe)
endif()

string(TIMESTAMP TODAY "%Y%m%d-%H%M")
set(REPORT_NAME "${TODAY}-Report.txt")

add_custom_target(
    run-scans
    DEPENDS cppcheck
    COMMAND ${STATIC_SCANNER_EXE} src/  --enable=all --output-file=${REPORT_NAME} 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
##########################################################################################
## Code Coverage 
##########################################################################################

# all of this only works with a gcc compiler and if gcov and lcov are installed
if(GCC_CODE_COVERAGE)
    # we need gcode and gcc, so lets make sure they are around
    if( NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(FATAL_ERROR "Must run code coverage builds on gcc, with gcov installed")
    endif()
    
    find_program(GCOV_BIN gcov)

    if(NOT GCOV_BIN)
        message(FATAL_ERROR "Must run code coverage builds on platform with gcov installed")
    endif()

    # turn on compile flags needed for gcov, disable exceptions and inlines to give a more accurate report of branch coverage
    SET(GCC_COVERAGE_COMPILE_FLAGS "-coverage -fprofile-arcs -ftest-coverage -fno-exceptions -fno-inline -fPIC -O0")
    SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

    # invoke this target only after building the project, and running the tests otherwise code coverage will be zero
    add_custom_target(
        code-cov-report
        COMMAND gcov -b -r 
            -s ${PROJECT_SOURCE_DIR} src/chess-lib-tests.cpp 
            -o ${PROJECT_BINARY_DIR}/src/CMakeFiles/chess-lib-tests.dir/
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
            --output-directory ${PROJECT_SOURCE_DIR}/code_coverage_report
            --rc genhtml_branch_coverage=1
     )

endif()

# Get the GoogleTest library and make it available for the project 
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

# override cmake's install location to put binaries in the root of the project
set(CMAKE_INSTALL_PREFIX  ${PROJECT_SOURCE_DIR}/install)

add_subdirectory(src)
