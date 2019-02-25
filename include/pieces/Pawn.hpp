#pragma once

#include <array>
#include <cstdint>

class Pawn
{
public:
  ~Pawn() = default;

  static void initialize();

	static std::array<std::uint64_t, 64> generateMoves(bool white);
  static void visDebug(int pos, bool white);

	static std::array<std::uint64_t, 64> getWhiteMoves() { return whiteMoves; }

	static std::array<std::uint64_t, 64> getBlackMoves() { return blackMoves; }

private:
	static std::array<std::uint64_t, 64> blackMoves;
	static std::array<std::uint64_t, 64> whiteMoves;
};