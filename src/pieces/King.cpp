#include "pieces/King.hpp"
#include "Board.hpp"

#include <iostream>
#include <bitset>

King::King() {
    initializeMoves();
}

King::~King() = default;

void King::initializeMoves() {
    bool canPlaceRight, canPlaceLeft, canPlaceAbove, canPlaceBelow;

    std::uint64_t bitShiftingBaseVal = 1;
    for (int i = 0; i < 64; ++i) {
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
}

void King::visDebug(int pos) {
    Board::visDebug(moves.at(pos));
}