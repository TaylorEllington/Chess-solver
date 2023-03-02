set(CHESS_LIB_SRC
    position.h
    board-utils.h
    move-generator.h

    board-utils.cpp
    move-generator.cpp
    position.cpp
)

add_library(chess-lib STATIC ${CHESS_LIB_SRC})



add_executable(chess-solver
        main.cpp
)

target_link_libraries( chess-solver
    chess-lib
)

add_executable( chess-lib-tests
    chess-lib-tests.cpp
)

target_link_libraries( chess-lib-tests
    chess-lib
    gtest_main
    gmock
)

if(GCC_STATIC_ANALYSIS)
    target_compile_options(chess-lib 
        PRIVATE ${GCC_STATIC_ANALYSIS_FLAGS}
    )
    
    target_compile_options(chess-lib-tests 
        PRIVATE ${GCC_STATIC_ANALYSIS_FLAGS}
    )

    target_compile_options(chess-solver 
        PRIVATE ${GCC_STATIC_ANALYSIS_FLAGS}
    )
endif()

gtest_discover_tests( chess-lib-tests)
