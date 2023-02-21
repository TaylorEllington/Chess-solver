#pragma once

#include <stdint.h>
#include <functional>
#include <string>

enum class Piece{
    NO_PEICE,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

enum class PieceColor{
    NO_COLOR,
    WHITE,
    BLACK,
};

Piece charToPiece(const char c);

uint8_t charToFile(const char c);

char pieceToChar(const Piece p);

char fileToChar(uint8_t);

struct Position{
    uint8_t rank;
    uint8_t file;
    bool takes = false;
    Piece piece;
    PieceColor color;

    Position();
    Position(uint8_t r, uint8_t f);

    Position(std::string str, PieceColor color);

    bool operator==(const Position& other) const {
        return rank == other.rank && file == other.file;
    }

    struct PositionHashFunction
    {
        size_t operator()(const Position& pos) const {
            size_t xHash = std::hash<int>()(pos.file);
            size_t yHash = std::hash<int>()(pos.rank) << 1;
            return xHash ^ yHash;

            return 0;
        }
    };
};





