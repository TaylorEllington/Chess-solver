add_subdirectory(sample-lib)
add_subdirectory(board-utils)
add_subdirectory(move-generator)


add_executable(chess-solver
        main.cpp
)

target_link_libraries( chess-solver
    board-utils
    move-generator
)
