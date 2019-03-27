#include "pieces/Pawn.hpp"
#include "Board.hpp"

std::array<std::uint64_t, 64> Pawn::whitePawnMoves;
std::array<std::uint64_t, 64> Pawn::blackPawnMoves;

void Pawn::initialize()
{
    whitePawnMoves = generateMoves(true);
    blackPawnMoves = generateMoves(false);
}

std::array<std::uint64_t, 64> Pawn::generateMoves(bool white)
{
	// Will only be bitshifted once
    std::array<std::uint64_t, 64> moves{};

    for (std::uint64_t i = 8; i < 56; ++i)
    {
	    moves.at(i) = 1ul << (i + (white ? 8 : -8));
        if (i % 8 != 0)
	        moves.at(i) += 1ul << (i + (white ? 7 : -9));
        if (i % 8 != 7)
	        moves.at(i) += 1ul << (i + (white ? 9 : -7));
        if ((i < 16 && white) || (i >= 48 && !white))
	        moves.at(i) += 1ul << (white ? i + 16 : i - 16);
    }

    return moves;
}