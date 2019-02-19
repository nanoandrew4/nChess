#include "pieces/Pawn.hpp"
#include "Board.hpp"

std::array<std::uint64_t, 48> Pawn::whiteMoves;
std::array<std::uint64_t, 48> Pawn::blackMoves;

void Pawn::initialize()
{
    whiteMoves = generateMoves(true);
    blackMoves = generateMoves(false);
}

std::array<std::uint64_t, 48> Pawn::generateMoves(bool white)
{
    std::uint64_t baseBit = 1; // Will only be bitshifted once
    std::array<std::uint64_t, 48> moves{};

    for (std::uint64_t i = 0; i < 48; ++i)
    {
        moves.at(i) = baseBit << (i + (white ? 16 : 0));
        if (i % 8 != 0)
            moves.at(i) += baseBit << (i + (white ? 15 : -1));
        if (i % 8 != 7)
            moves.at(i) += baseBit << (i + (white ? 17 : 1));
        if ((i < 8 && white) || (i >= 40 && !white))
            moves.at(i) += baseBit << (white ? i + 24 : i - 8);
    }

    return moves;
}

void Pawn::visDebug(int pos, bool white)
{
    Board::visDebug(white ? whiteMoves.at(pos) : blackMoves.at(pos));
}