#include "move-generator.h"

#include <math.h>

namespace move_generator{

    std::vector<Position> GeneratePawnMoves(Position pos, BoardState const & board){
        std::vector<Position> moves;
        Position moveForward(pos);
        Position attackLeft(pos);
        Position attackRight(pos);
        // pawns only move "forward" based on their starting location, so we need 
        // different logic for black and white pawns.

        switch(pos.color){
            case PieceColor::WHITE:
                moveForward.rank++;
                if(!board_utils::isOccupied(moveForward, board)){
                    moves.push_back(moveForward);

                    // Pawns can move two squares on their first turn
                    moveForward.rank++;
                    if(pos.rank == 2 && !board_utils::isOccupied(moveForward, board)){
                        moves.push_back(moveForward);
                    }
                }

                // pawns capture diagonally
                attackRight.rank++;
                attackRight.file++;
                if(board_utils::isOccupiedByEnemy(attackRight, board) && board_utils::isValidPosition(attackRight)){
                    attackRight.takes = true;
                    moves.push_back(attackRight);
                }

                attackLeft.rank++;
                attackLeft.file--;
                if(board_utils::isOccupiedByEnemy(attackLeft, board) && board_utils::isValidPosition(attackLeft)){
                    attackLeft.takes = true;
                    moves.push_back(attackLeft);
                }

                break;
            case PieceColor::BLACK:
                moveForward.rank--;
                if(!board_utils::isOccupied(moveForward, board)){
                    moves.push_back(moveForward);

                    // Pawns can move two squares on their first turn
                    moveForward.rank--;
                    if(pos.rank == 7 && !board_utils::isOccupied(moveForward, board)){
                        moves.push_back(moveForward);
                    }
                }

                // pawns capture diagonally
                attackRight.rank--;
                attackRight.file++;
                if(board_utils::isOccupiedByEnemy(attackRight, board) && board_utils::isValidPosition(attackRight)){
                    attackRight.takes = true;
                    moves.push_back(attackRight);
                }

                attackLeft.rank--;
                attackLeft.file--;
                if(board_utils::isOccupiedByEnemy(attackLeft, board) && board_utils::isValidPosition(attackLeft)){
                    attackLeft.takes = true;
                    moves.push_back(attackLeft);
                }
                break;
        }
        return moves;
    }

    std::vector<Position> GenerateRookMoves(Position pos, BoardState const & board){
        std::vector<Position> moves;

        for(int ii = pos.rank - 1; ii > 0; ii--){
            Position potentialMove(pos);
            potentialMove.rank = ii;

            if(!board_utils::isValidPosition(potentialMove)){
                break;
            }

            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                break;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                break;
            }

            moves.push_back(potentialMove);

        }

        for(int ii = pos.rank + 1; ii < 9 ; ii++){
            Position potentialMove(pos);
            potentialMove.rank = ii;

            if(!board_utils::isValidPosition(potentialMove)){
                break;
            }
            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                break;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                break;
            }

            moves.push_back(potentialMove);
            
        }

        for(int ii = pos.file - 1; ii > 0; ii--){
            Position potentialMove(pos);
            potentialMove.file = ii;

            if(!board_utils::isValidPosition(potentialMove)){
                break;
            }

            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                break;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                break;
            }

            moves.push_back(potentialMove);
        }

        for(int ii = pos.file + 1; ii < 9 ; ii++){
            Position potentialMove(pos);
            potentialMove.file = ii;

            if(!board_utils::isValidPosition(potentialMove)){
                break;
            }
            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                break;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                break;
            }

            moves.push_back(potentialMove);
        }

        return moves;
    }

    std::vector<Position> GenerateKnightMoves(Position pos, BoardState const & board){
        std::vector<Position> moves;

        std::pair<signed int, signed int> moveTable[] = {
            { 1,  2}, { 2,  1},
            { 1, -2}, { 2, -1},
            {-1, -2}, {-2, -1},
            {-1,  2}, {-2,  1},
        };

        for(int ii = 0; ii < 8; ii++){
            Position potentialMove(pos);
            potentialMove.rank += moveTable[ii].first;
            potentialMove.file += moveTable[ii].second;

            if(!board_utils::isValidPosition(potentialMove)){
                continue;
            }

            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                continue;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                continue;
            }
            moves.push_back(potentialMove);
        }

        return moves;
    }

    std::vector<Position> GenerateBishiopMoves(Position pos, BoardState const & board){
        std::vector<Position> moves;

        for(int ii = 1; ii <= std::min(8 - pos.file, 8 - pos.rank); ii++){
            Position potentialMove(pos);
            potentialMove.rank += ii;
            potentialMove.file += ii;
        
            if(!board_utils::isValidPosition(potentialMove)){
                break;
            }

            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                break;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                break;
            }

            moves.push_back(potentialMove);
        }

        for(int ii = 1; ii <= std::min(8 - pos.file,0 + pos.rank); ii++){
            Position potentialMove(pos);
            potentialMove.rank -= ii;
            potentialMove.file += ii;
        
            if(!board_utils::isValidPosition(potentialMove)){
                break;
            }

            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                break;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                break;
            }

            moves.push_back(potentialMove);
        }

        for(int ii = 1; ii <= std::min( pos.file, pos.rank); ii++){
            Position potentialMove(pos);
            potentialMove.rank -= ii;
            potentialMove.file -= ii;
        
            if(!board_utils::isValidPosition(potentialMove)){
                break;
            }

            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                break;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                break;
            }

            moves.push_back(potentialMove);
        }

        for(int ii = 1; ii <= std::min( pos.file, pos.rank); ii++){
            Position potentialMove(pos);
            potentialMove.rank += ii;
            potentialMove.file -= ii;
        
            if(!board_utils::isValidPosition(potentialMove)){
                break;
            }

            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                moves.push_back(potentialMove);
                break;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                break;
            }

            moves.push_back(potentialMove);
        }
        return moves;
    }

    std::vector<Position> GenerateQueenMoves(Position pos, BoardState const & board){
        std::vector<Position> moves;
        std::vector<Position> bmoves = GenerateBishiopMoves(pos, board);
        std::vector<Position> rmoves = GenerateRookMoves(pos, board);

        moves.reserve(bmoves.size() + rmoves.size());
        moves.insert(moves.end(), bmoves.begin(), bmoves.end());
        moves.insert(moves.end(), rmoves.begin(), rmoves.end());

        return moves;
    }

    std::vector<Position> GenerateKingMoves(Position pos, BoardState const & board){
        std::vector<Position> possibleMoves;

        std::pair<signed int, signed int> moveTable[] = {
            {  1,   1}, {  1,  0},
            { -1,   1}, { -1,  0},
            {  1,  -1}, {  1,  -0},
            { -1,  -1}, { -1,  -0}
        };

        for(int ii = 0; ii < 8; ii++){
            Position potentialMove(pos);
            potentialMove.rank += moveTable[ii].first;
            potentialMove.file += moveTable[ii].second;

            if(!board_utils::isValidPosition(potentialMove)){
                continue;
            }

            if(board_utils::isOccupiedByEnemy(potentialMove, board)){
                potentialMove.takes = true;
                possibleMoves.push_back(potentialMove);
                continue;
            }

            if(board_utils::isOccupied(potentialMove, board)){
                continue;
            }
            possibleMoves.push_back(potentialMove);
        }

        return possibleMoves;
    }


}