#include "pieces/Knight.hpp"
#include "Board.hpp"

Knight::Knight()
{
    initializeMoves();
}

Knight::~Knight()
{
}

void Knight::visDebug(int pos)
{
    Board::visDebug(moves.at(pos));
}

void Knight::initializeMoves()
{
    std::uint64_t baseBit = 1;
    for (int i = 0; i < 64; ++i)
    {
        std::uint64_t move = 0;
        if (i < 48 && i % 8 >= 1) // Up 2, right 1
            move += baseBit << (i + 15);
        if (i < 56 && i % 8 >= 2) // Up 1, right 2
            move += baseBit << (i + 6);
        if (i >= 8 && i % 8 >= 2) // Down 1, right 2
            move += baseBit << (i - 10);
        if (i >= 16 && i % 8 >= 1) // Down 2, right 1
            move += baseBit << (i - 17);
        if (i >= 16 && i % 8 < 7) // Down 2, left 1
            move += baseBit << (i - 15);
        if (i >= 8 && i % 8 < 6) // Down 1, left 2
            move += baseBit << (i - 6);
        if (i < 56 && i % 8 < 6) // Up 1, left 2
            move += baseBit << (i + 10);
        if (i < 48 && i % 8 < 7) // Up 2, left 1
            move += baseBit << (i + 17);

        moves.at(i) = move;
    }
}