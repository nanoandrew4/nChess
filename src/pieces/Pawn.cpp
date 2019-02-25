#include "pieces/Pawn.hpp"
#include "Board.hpp"

std::array<std::uint64_t, 64> Pawn::whiteMoves;
std::array<std::uint64_t, 64> Pawn::blackMoves;

void Pawn::initialize()
{
    whiteMoves = generateMoves(true);
    blackMoves = generateMoves(false);
}

std::array<std::uint64_t, 64> Pawn::generateMoves(bool white)
{
    std::uint64_t baseBit = 1; // Will only be bitshifted once
    std::array<std::uint64_t, 64> moves{};

    for (std::uint64_t i = 8; i < 56; ++i)
    {
        moves.at(i) = baseBit << (i + (white ? 8 : -8));
        if (i % 8 != 0)
            moves.at(i) += baseBit << (i + (white ? 7 : -9));
        if (i % 8 != 7)
            moves.at(i) += baseBit << (i + (white ? 9 : -7));
        if ((i < 16 && white) || (i >= 48 && !white))
            moves.at(i) += baseBit << (white ? i + 16 : i - 16);
    }

    return moves;
}

void Pawn::visDebug(int pos, bool white)
{
    Board::visDebug(white ? whiteMoves.at(pos) : blackMoves.at(pos));
}