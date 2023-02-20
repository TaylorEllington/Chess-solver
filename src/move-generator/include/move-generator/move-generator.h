#pragma once
#include "board-utils/position.h"
#include "board-utils/board-utils.h"
#include <vector>


namespace move_generator{

    std::vector<Position> GeneratePawnMoves(Position pos, BoardState board);
    std::vector<Position> GenerateRookMoves(Position pos, BoardState board);
    std::vector<Position> GenerateKnightMoves(Position pos, BoardState board);
    std::vector<Position> GenerateBishiopMoves(Position pos, BoardState board);
    std::vector<Position> GenerateQueenMoves(Position pos, BoardState board);
    std::vector<Position> GenerateKingMoves(Position pos, BoardState board);

}