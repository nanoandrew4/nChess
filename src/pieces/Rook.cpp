#include "pieces/Rook.hpp"
#include "Board.hpp"

std::array<std::uint64_t, 64> Rook::moves;

void Rook::initialize () {
    moves = generateMoves();
}

std::array<std::uint64_t, 64> Rook::generateMoves() {
    std::array<std::uint64_t, 64> moves{};
    std::uint64_t baseBit = 1;

    for (unsigned long i = 0; i < 64; ++i) {
        // Horizontal moves
        std::uint64_t move = 0;
        for (unsigned long j = i + (7 - (i % 8)); j >= i - (i % 8); --j)
            if (j != i)
                move += baseBit << j;
        // Vertical moves
        for (unsigned long j = i % 8; j < 64; j += 8)
            if (j != i)
                move += baseBit << j;
        moves.at(i) = move;
    }

    return moves;
}

void Rook::visDebug(unsigned long pos) {
    Board::visDebug(moves.at(pos));
}

