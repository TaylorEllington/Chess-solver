#pragma once
#include "position.h"
#include "board-utils.h"
#include <vector>


namespace move_generator{

    std::vector<Position> GeneratePawnMoves(Position pos, BoardState const & board);
    std::vector<Position> GenerateRookMoves(Position pos, BoardState const & board);
    std::vector<Position> GenerateKnightMoves(Position pos, BoardState const & board);
    std::vector<Position> GenerateBishiopMoves(Position pos, BoardState const & board);
    std::vector<Position> GenerateQueenMoves(Position pos, BoardState const & board);
    std::vector<Position> GenerateKingMoves(Position pos, BoardState const & board);

}