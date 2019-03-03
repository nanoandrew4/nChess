#include "pieces/King.hpp"
#include "Board.hpp"

#include <bitset>

std::array<std::uint64_t, 64> King::whiteMoves;
std::array<std::uint64_t, 64> King::blackMoves;

void King::initialize() {
    whiteMoves = generateMoves(true);
    blackMoves = generateMoves(false);
}

std::array<std::uint64_t, 64> King::generateMoves(bool white) {
    bool canPlaceRight, canPlaceLeft, canPlaceAbove, canPlaceBelow;
    std::array<std::uint64_t, 64> moves{};
    std::uint64_t bitShiftingBaseVal = 1;

    for (unsigned long i = 0; i < 64; ++i) {
        std::uint64_t move = 0;

        canPlaceLeft = (i + 1) % 8 != 0;
        canPlaceRight = i % 8 != 0; 
        canPlaceAbove = i <= 55;
        canPlaceBelow = i >= 8;

        if (canPlaceRight)
            move += bitShiftingBaseVal << (i - 1);
        if (canPlaceLeft)
            move += bitShiftingBaseVal << (i + 1);
        if (canPlaceAbove) 
            move += bitShiftingBaseVal << (i + 8);
        if (canPlaceBelow)
            move += bitShiftingBaseVal << (i - 8);
        if (canPlaceRight && canPlaceAbove)
            move += bitShiftingBaseVal << (i + 7);
        if (canPlaceLeft && canPlaceAbove)
            move += bitShiftingBaseVal << (i + 9);
        if (canPlaceLeft && canPlaceBelow)
            move += bitShiftingBaseVal << (i - 7);
        if (canPlaceRight && canPlaceBelow)
            move += bitShiftingBaseVal << (i - 9);

        moves.at(i) = move;
    }

    if (white)
        moves.at(3) += (bitShiftingBaseVal << 1L) + (bitShiftingBaseVal << 5L);
    else
        moves.at(58) += (bitShiftingBaseVal << 60L) + (bitShiftingBaseVal << 56L);

    return moves;
}

void King::visDebug(bool white, unsigned long pos) {
    Board::visDebug(white ? whiteMoves.at(pos) : blackMoves.at(pos));
}