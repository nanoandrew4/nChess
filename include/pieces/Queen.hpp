#pragma once

#include <array>
#include <cstdlib>

class Queen
{
  public:
    ~Queen() = default;

    static void initialize();
    static std::array<std::uint64_t, 64> generateMoves();
    static void visDebug(unsigned long pos);

  private:
    static std::array<std::uint64_t, 64> moves;
};