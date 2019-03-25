#pragma once

#include <array>
#include <cstdlib>

class Queen
{
  public:
    ~Queen() = default;

    static void initialize();
    static std::array<std::uint64_t, 64> generateMoves();

	static std::array<std::uint64_t, 64> getMoves() { return queenMoves; }

  private:
	static std::array<std::uint64_t, 64> queenMoves;
};