#include "pieces/Pawn.hpp"
#include "Board.hpp"

Pawn::Pawn()
{
    initializeMoves();
}

Pawn::~Pawn()
{
}

void Pawn::initializeMoves()
{
    for (int i = 0; i < 48; ++i) {
        std::uint64_t baseBit = 1; // Will only be bitshifted once
        whiteMoves.at(i) = baseBit << (i + 16);
        blackMoves.at(47 - i) = baseBit << i;
    }
}

void Pawn::visDebug(int pos, bool white) {
    Board::visDebug(white ? whiteMoves.at(pos) : blackMoves.at(pos));
}