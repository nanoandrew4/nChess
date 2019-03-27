#include "pieces/Rook.hpp"
#include "Board.hpp"

std::array<std::uint64_t, 64> Rook::rookMoves;

void Rook::initialize () {
    rookMoves = generateMoves();
}

std::array<std::uint64_t, 64> Rook::generateMoves() {
    std::array<std::uint64_t, 64> moves{};

    for (unsigned long i = 0; i < 64; ++i) {
        // Horizontal moves
        std::uint64_t move = 0;
	    for (unsigned long j = i + (7 - (i % 8)); j >= i - (i % 8) && j < 64; --j)
            if (j != i)
	            move += 1ul << j;
        // Vertical moves
        for (unsigned long j = i % 8; j < 64; j += 8)
            if (j != i)
	            move += 1ul << j;
        moves.at(i) = move;
    }

    return moves;
}