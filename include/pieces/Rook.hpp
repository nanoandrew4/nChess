#pragma once

#include <array>
#include <cstdlib>

class Rook
{
  public:
    ~Rook() = default;

  static void initialize();
    static std::array<std::uint64_t, 64> generateMoves();
    static void visDebug(int pos);

  private:
    static std::array<std::uint64_t, 64> moves;
};