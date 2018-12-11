#include "pieces/Bishop.hpp"
#include "Board.hpp"

Bishop::Bishop()
{
    initializeMoves();
}

Bishop::~Bishop()
{
}

void Bishop::initializeMoves()
{
    std::uint64_t baseBit = 1;
    for (int i = 0; i < 64; ++i)
    {
        std::uint64_t move = 0;
        for (int j = i + 7; i % 8 != 0 && (j + 1) % 8 != 0 && j < 64; j += 7) // Piece to top right diagonal
            move += baseBit << j;
        for (int j = i - 7; i % 8 != 0 && (j + 1) % 8 != 0 && j >= 0; j -= 7) // Piece to bottom left diagonal
            move += baseBit << j;
        for (int j = i + 9; (i + 1) % 8 != 0 && j % 8 != 0 && j < 64; j += 9) // Piece to top left diagonal
            move += baseBit << j;
        for (int j = i - 9; (i + 1) % 8 != 0 && j % 8 != 0 && j >= 0; j -= 9) // Piece to bottom right diagonal
            move += baseBit << j;

        moves.at(i) = move;
    }
}

void Bishop::visDebug(int pos)
{
    Board::visDebug(moves.at(pos));
}