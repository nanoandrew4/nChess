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
    std::array<std::uint64_t, 48> moves;

    for (int i = 0; i < 48; ++i)
        moves.at(white ? i : (47 - i)) = baseBit << (i + (white ? 16 : 0));

    return moves;
}

void Pawn::visDebug(int pos, bool white)
{
    Board::visDebug(white ? whiteMoves.at(pos) : blackMoves.at(pos));
}