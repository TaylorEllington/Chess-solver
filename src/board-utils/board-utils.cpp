#include "include/board-utils/board-utils.h"

#include <sstream>
#include <iostream>
#include <exception>
namespace board_utils{
    BoardState BuildBoardFromString(std::string WhitePiecesString, std::string BlackPiecesString){
        std::stringstream wss(WhitePiecesString);
        std::stringstream bss(BlackPiecesString);

        std::string word;
        BoardState board;

        while(wss >> word){
            Position pos(word, PieceColor::WHITE);
            if(board.find(pos) != board.end()){
                throw std::runtime_error("Invalid board state provided, each square can hold one piece, each piece should only be listed once in notation");
            }

            board.insert(pos);
        }

        while(bss >> word){
            Position pos(word, PieceColor::BLACK);
            if(board.find(pos) != board.end()){
                throw std::runtime_error("Invalid board state provided, each square can hold one piece, each piece should only be listed once in notation");
            }
            board.insert(pos);
        }


        return board;
    }
    bool isOccupied(Position pos, BoardState board){
        
        size_t count = board.count(pos);

        if(count == 0){
            return false;
        }

        return true;
        
    }
    bool isOccupiedByEnemy(Position pos, BoardState board){
        size_t count = board.count(pos);


        if(count == 0){
            return false;
        }

        auto otherPiece = board.find(pos);
        if(pos.color == otherPiece->color){
            return false;
        }

            // if(auto otherPiece = board.find(pos); *otherPiece. )

        return true;
    }
    bool isValidPosition(Position pos){
        
        if(pos.file < 1 || pos.file > 8){
            return false;
        }

        if(pos.rank < 1 || pos.rank > 8){
            return false;
        }

        return true;
    }
    std::string printAsMove(Position pos){
        std::stringstream output;

        output << pieceToChar(pos.piece);
        if(pos.takes){
            output << "x";
        }
        output << fileToChar(pos.file);
        output << std::to_string((char)pos.rank);

        return output.str();

    }
    std::vector<std::string> movesToStrings(std::vector<Position> & moves){
        std::vector<std::string> moveStrings;
        
        for(auto move : moves){
            moveStrings.push_back(printAsMove(move));
        }

        return moveStrings;
    }

    std::string joinAllMoves(std::vector<std::string> moves){
        std::stringstream output;

        for(auto move: moves){
            output << move << " ";
        }

        return output.str();
    }

}