#include "pieces/Bishop.hpp"
#include "Board.hpp"

std::array<std::uint64_t, 64> Bishop::bishopMoves;

void Bishop::initialize()
{
    bishopMoves = generateMoves();
}

std::array<std::uint64_t, 64> Bishop::generateMoves()
{
    std::array<std::uint64_t, 64> moves{};

    for (int i = 0; i < 64; ++i)
    {
        std::uint64_t move = 0;
        // Piece to top right diagonal
        for (int j = i + 7; i % 8 != 0 && (j + 1) % 8 != 0 && j < 64; j += 7)
	        move += 1UL << (std::uint64_t) j;
        // Piece to bottom left diagonal
        for (int j = i - 7; (i + 1) % 8 != 0 && j % 8 != 0 && j >= 0; j -= 7)
	        move += 1UL << (std::uint64_t) j;
        // Piece to top left diagonal
        for (int j = i + 9; (i + 1) % 8 != 0 && j % 8 != 0 && j < 64; j += 9)
	        move += 1UL << (std::uint64_t) j;
        // Piece to bottom right diagonal
        for (int j = i - 9; i % 8 != 0 && (j + 1) % 8 != 0 && j >= 0; j -= 9)
	        move += 1UL << (std::uint64_t) j;

        moves.at(static_cast<unsigned long>(i)) = move;
    }

    return moves;
}