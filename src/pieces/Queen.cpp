#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "Board.hpp"

std::array<std::uint64_t, 64> Queen::queenMoves;

void Queen::initialize() {
    queenMoves = generateMoves();
}

std::array<std::uint64_t, 64> Queen::generateMoves() {
    std::array<std::uint64_t, 64> moves{};

    std::array<std::uint64_t, 64> rookMoves = Rook::generateMoves();
    std::array<std::uint64_t, 64> bishopMoves = Bishop::generateMoves();

    for (unsigned long i = 0; i < 64; ++i)
        moves.at(i) = rookMoves.at(i) | bishopMoves.at(i);

    return moves;
 }