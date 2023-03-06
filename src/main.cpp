#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "board-utils.h"
#include "move-generator.h"

int main(int argc, char** argv){

    if(argc < 2){
        std::cout << "You must specify a properly formatted input file" << std::endl;
        return 1;
    }

    std::ifstream inputFile;
    inputFile.open(argv[1], std::ios_base::binary);
    inputFile.seekg(0, std::ios_base::end);
    size_t filesize = inputFile.tellg();
    inputFile.seekg(0, std::ios_base::beg);


    std::vector<char> fileContents(filesize + 1, '\0');

    inputFile.read(fileContents.data(), filesize);
    fileContents.erase(std::remove(fileContents.begin(), fileContents.end(), ','), fileContents.end());

    auto firstLineTerminator = std::find(fileContents.begin(), fileContents.end(), '\n');
    auto secondLineTerminator = std::find(firstLineTerminator + 1, fileContents.end(), '\n');
    auto thirdLineTerminator = std::find(secondLineTerminator + 1, fileContents.end(), '\0');
    std::string white =  std::string(fileContents.begin(), firstLineTerminator - 1);
    std::string black =std::string(firstLineTerminator + 1, secondLineTerminator - 1);
    std::string pieceToMove = std::string(secondLineTerminator + 1, thirdLineTerminator);

    auto colonLocation = std::find(white.begin(), white.end(), ':');
    white.erase(white.begin(), colonLocation + 1 );

    colonLocation = std::find(black.begin(), black.end(), ':');
    black.erase(black.begin(), colonLocation + 1 );

    colonLocation = std::find(pieceToMove.begin(), pieceToMove.end(), ':');
    pieceToMove.erase(pieceToMove.begin(), colonLocation + 1 );

    BoardState bs = board_utils::BuildBoardFromString(white, black);

    PieceColor color = PieceColor::BLACK;
    if(white.find(pieceToMove) != std::string::npos){
        color = PieceColor::WHITE;
    }

    Position p(pieceToMove, color);

    std::vector<Position> moves;

        switch(p.piece){
            case Piece::PAWN:
                moves = move_generator::GeneratePawnMoves(p, bs);
                break;
            case Piece::ROOK:
                moves = move_generator::GenerateRookMoves(p, bs);
                break;
            case Piece::KNIGHT:
                moves = move_generator::GenerateKnightMoves(p, bs);
                break;
            case Piece::BISHOP:
                moves = move_generator::GenerateBishiopMoves(p, bs);
                break;
            case Piece::QUEEN:
                moves = move_generator::GenerateQueenMoves(p, bs);
                break;
            case Piece::KING:
                moves = move_generator::GenerateKingMoves(p, bs);
                break;
        }

    std::string moveString = board_utils::joinAllMoves( board_utils::movesToStrings(moves));


    std::cout <<"Legal moves for " << pieceToMove << ": " << moveString << std::endl;

    return 0;
}