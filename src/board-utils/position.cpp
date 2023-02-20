#include "include/board-utils/position.h"


Piece charToPiece(const char c){
    switch(c){
        case 'P':
            return Piece::PAWN;
        case 'R':
            return Piece::ROOK;
        case 'N':
            return Piece::KNIGHT;
        case 'B':
            return Piece::BISHOP;
        case 'Q':
            return Piece::QUEEN;
        case 'K':
            return Piece::KING;
    }
};

uint8_t charToFile(const char c){
    switch(c){
        case 'a':
            return 1;
        case 'b':
            return 2;
        case 'c':
            return 3;
        case 'd':
            return 4;
        case 'e':
            return 5;
        case 'f':
            return 6;
        case 'g':
            return 7;
        case 'h':
            return 8;
    }
};

char pieceToChar(const Piece p){
    switch(p){
        case Piece::PAWN:
            return 'P';
        case Piece::ROOK:
            return 'R';
        case Piece::KNIGHT:
            return 'N';
        case Piece::BISHOP:
            return 'B';
        case Piece::QUEEN:
            return 'Q';
        case Piece::KING:
            return 'K';
    }
}

char fileToChar(uint8_t f){
    switch(f){
        case 1:
            return 'a';
        case 2:
            return 'b';
        case 3:
            return 'c';
        case 4:
            return 'd';
        case 5:
            return 'e';
        case 6:
            return 'f';
        case 7:
            return 'g';
        case 8:
            return 'h';
    }
};

Position::Position(){}
Position::Position(uint8_t r, uint8_t f){
        rank = r;
        file = f;
    }

Position::Position(std::string str, PieceColor color){
        // we have no guarantee the string is a 3 letter notation. it could contain extra leading or trailing spaces
        // We will operate under the assumption that a notation will at least be properly in order
        this->color = color;

        uint8_t parsedValues = 0;

        for(const char& c : str){
            if(isspace(c) ){
                continue;
            }

            switch(parsedValues){
                case 0:
                    piece = charToPiece(c);
                    parsedValues++;
                    continue;
                case 1:
                    file = charToFile(c);
                    parsedValues++;
                    continue;
                case 2:
                    rank = c - '0';
                    parsedValues++;
                    continue;
                default:
                    return;
            }
            
        }

    }