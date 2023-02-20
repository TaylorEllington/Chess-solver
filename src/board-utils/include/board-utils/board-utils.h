#pragma once
#include "position.h"
#include <unordered_set>
#include <string>
typedef  std::unordered_set<Position, Position::PositionHashFunction> BoardState;



namespace board_utils{
    BoardState BuildBoardFromString(std::string WhitePiecesString, std::string BlackPiecesString);
    bool isOccupied(Position pos, BoardState board);
    bool isValidPosition(Position);
    bool isOccupiedByEnemy(Position pos, BoardState board);
    std::string printAsMove(Position pos);
    std::vector<std::string> movesToStrings(std::vector<Position> & moves);
    std::string joinAllMoves(std::vector<std::string> moves);
}