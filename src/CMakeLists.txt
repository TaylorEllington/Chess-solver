
add_subdirectory(board-utils)
add_subdirectory(move-generator)


add_executable(chess-solver
        main.cpp
)

target_link_libraries( chess-solver
    board-utils
    move-generator
)


if(CODE_COVERAGE)
    add_custom_target( gcov 
    COMMAND mkdir -p _coverage
    COMMAND ctest --test-dir _build/
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )

    set(CPP_FILES "")
    foreach(SRC_FILE ${SOURCES_FOR_CODE_COVERAGE})
        if(${SRC_FILE} MATCHES ".cpp")
            list(APPEND CPP_FILES ${SRC_FILE})
        endif()
    endforeach()

    STRING(JOIN " " CMD_STR ${CPP_FILES})

    message(FATAL_ERROR ${CMD_STR})

    add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMD_STR} -o ${OBJECT_DIR}
        | grep -A 5 "Adder.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage  # Need separate command for this line
    )
endif()