#include "pieces/King.hpp"
#include "Board.hpp"

#include <bitset>

std::array<std::uint64_t, 64> King::whiteKingMoves;
std::array<std::uint64_t, 64> King::blackKingMoves;
std::array<std::uint64_t, 64> King::nonCastleKingMoves;

void King::initialize() {
	whiteKingMoves = generateMoves(true, true);
	blackKingMoves = generateMoves(false, true);
	nonCastleKingMoves = generateMoves(false, false);
}

std::array<std::uint64_t, 64> King::generateMoves(bool white, bool includeCastleMoves) {
    bool canPlaceRight, canPlaceLeft, canPlaceAbove, canPlaceBelow;
    std::array<std::uint64_t, 64> moves{};

    for (unsigned long i = 0; i < 64; ++i) {
        std::uint64_t move = 0;

        canPlaceLeft = (i + 1) % 8 != 0;
        canPlaceRight = i % 8 != 0; 
        canPlaceAbove = i <= 55;
        canPlaceBelow = i >= 8;

        if (canPlaceRight)
	        move += 1UL << (i - 1);
        if (canPlaceLeft)
	        move += 1UL << (i + 1);
        if (canPlaceAbove)
	        move += 1UL << (i + 8);
        if (canPlaceBelow)
	        move += 1UL << (i - 8);
        if (canPlaceRight && canPlaceAbove)
	        move += 1UL << (i + 7);
        if (canPlaceLeft && canPlaceAbove)
	        move += 1UL << (i + 9);
        if (canPlaceLeft && canPlaceBelow)
	        move += 1UL << (i - 7);
        if (canPlaceRight && canPlaceBelow)
	        move += 1UL << (i - 9);

        moves.at(i) = move;
    }

	if (white && includeCastleMoves)
	    moves.at(3) += (1UL << 1L) + (1UL << 5L);
	else if (includeCastleMoves)
	    moves.at(59) += (1LU << 61L) + (1LU << 57L);

    return moves;
}