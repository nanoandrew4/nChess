#pragma once

#include <array>
#include <cstdint>

class Pawn
{
  public:
    Pawn();
    ~Pawn();

    void visDebug(int pos, bool white);
  private:
    std::array<std::uint64_t, 48> blackMoves;
    std::array<std::uint64_t, 48> whiteMoves;

    void initializeMoves();
};