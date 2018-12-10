#include "pieces/Rook.hpp"
#include "Board.hpp"

Rook::Rook() {
    initializeMoves();
}

Rook::~Rook() {

}

void Rook::initializeMoves() {
    std::uint64_t baseBit = 1;
    for (int i = 0; i < 64; ++i) {
        // Horizontal moves
        std::uint64_t move = 0;
        for (int j = i + (7 - (i % 8)); j >= i - (i % 8); --j)
            if (j != i)
                move += baseBit << j;
        // Vertical moves
        for (int j = i % 8; j < 64; j += 8)
            if (j != i)
                move += baseBit << j;
        moves.at(i) = move;
    }
}

void Rook::visDebug(int pos) {
    Board::visDebug(moves.at(pos));
}

