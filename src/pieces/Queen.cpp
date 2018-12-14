#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "Board.hpp"

std::array<std::uint64_t, 64> Queen::moves;

void Queen::initialize() {
    moves = generateMoves();
}

std::array<std::uint64_t, 64> Queen::generateMoves() {
    std::array<std::uint64_t, 64> moves;

    std::array<std::uint64_t, 64> rookMoves = Rook::generateMoves();
    std::array<std::uint64_t, 64> bishopMoves = Bishop::generateMoves();

    for (int i = 0; i < 64; ++i)
        moves.at(i) = rookMoves.at(i) | bishopMoves.at(i);

    return moves;
 }

 void Queen::visDebug(int pos) {
     Board::visDebug(moves.at(pos));
 }