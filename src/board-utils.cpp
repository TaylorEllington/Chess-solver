#include "board-utils.h"

#include <sstream>
#include <iostream>
namespace board_utils{
    BoardState BuildBoardFromString(std::string WhitePiecesString, std::string BlackPiecesString){
        std::stringstream wss(WhitePiecesString);
        std::stringstream bss(BlackPiecesString);

        std::string word;
        BoardState board;

        while(wss >> word){
            Position pos(word, PieceColor::WHITE);
            if(board.find(pos) != board.end()){
                std::cout << "Invalid board state provided, each square can hold one piece, each piece should only be listed once in notation" << std::endl;
                exit(1);
            }

            board.insert(pos);
        }

        while(bss >> word){
            Position pos(word, PieceColor::BLACK);
            if(board.find(pos) != board.end()){
                std::cout << "Invalid board state provided, each square can hold one piece, each piece should only be listed once in notation" << std::endl;
                exit(1);
            }
            board.insert(pos);
        }


        return board;
    }
    bool isOccupied(Position pos, BoardState board){
        
        auto otherPiece = board.find(pos);
        if(otherPiece == board.end()){
            return false;
        }

        return true;
        
    }
    bool isOccupiedByEnemy(Position pos, BoardState board){

        auto otherPiece = board.find(pos);
        if(otherPiece == board.end() || pos.color == otherPiece->color){
            return false;
        }
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