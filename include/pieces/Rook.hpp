#pragma once

#include <array>
#include <cstdlib>

class Rook
{
public:
  ~Rook() = default;

  static void initialize();
  static std::array<std::uint64_t, 64> generateMoves();

	const static std::array<std::uint64_t, 64> getMoves() { return rookMoves; }

private:
	static std::array<std::uint64_t, 64> rookMoves;
};