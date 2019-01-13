#pragma once

#include <array>
#include <cstdlib>

class Knight
{

  public:
    ~Knight() = default;

    static void initialize();
    static std::array<std::uint64_t, 64> generateMoves();
    static void visDebug(int pos);
    static std::array<std::uint64_t, 64> getMoves() { return moves; }

  private:
    static std::array<std::uint64_t, 64> moves;
};