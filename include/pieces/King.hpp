#pragma once

#include <array>
#include <cstdint>

class King
{
  public:
    ~King() = default;

    static void initialize();
    static std::array<std::uint64_t, 64> generateMoves();
    static void visDebug(unsigned long pos);

	static std::array<std::uint64_t, 64> getMoves() { return moves; }

  private:
    static std::array<std::uint64_t, 64> moves;
};