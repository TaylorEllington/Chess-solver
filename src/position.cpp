#include "position.h"


Piece charToPiece(const char c){

    Piece p = Piece::NO_PEICE;

    switch(c){
        case 'P':
            p = Piece::PAWN;
            break;
        case 'R':
            p = Piece::ROOK;
            break;
        case 'N':
            p = Piece::KNIGHT;
            break;
        case 'B':
            p = Piece::BISHOP;
            break;
        case 'Q':
            p = Piece::QUEEN;
            break;
        case 'K':
            p = Piece::KING;
            break;
        default:
            break;
    }

    return p;
};

uint8_t charToFile(const char c){
    uint8_t i = 0;

    switch(c){
        case 'a':
            i = 1;
            break;
        case 'b':
            i = 2;
            break;
        case 'c':
            i = 3;
            break;
        case 'd':
            i = 4;
            break;
        case 'e':
            i = 5;
            break;
        case 'f':
            i = 6;
            break;
        case 'g':
            i = 7;
            break;
        case 'h':
            i = 8;
            break;
        default:
            break;
    }

    return i;
};

char pieceToChar(const Piece p){
    char c = 'X';

    switch(p){
        case Piece::PAWN:
            c = 'P';
            break;
        case Piece::ROOK:
            c = 'R';
            break;
        case Piece::KNIGHT:
            c = 'N';
            break;
        case Piece::BISHOP:
            c = 'B';
            break;
        case Piece::QUEEN:
            c = 'Q';
            break;
        case Piece::KING:
            c = 'K';
            break;
        case Piece::NO_PEICE:
            c = 'X';
            break;
    }
    return c;
}

char fileToChar(uint8_t f){
    char c = 'x';
    switch(f){
        case 1:
            c = 'a';
            break;
        case 2:
            c = 'b';
            break;
        case 3:
            c = 'c';
            break;
        case 4:
            c = 'd';
            break;
        case 5:
            c = 'e';
            break;
        case 6:
            c = 'f';
            break;
        case 7:
            c = 'g';
            break;
        case 8:
            c = 'h';
            break;
        default:
            break;
    }

    return c;
};

Position::Position(){}

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
            }
            
        }

    }