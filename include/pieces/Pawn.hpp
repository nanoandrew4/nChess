#pragma once

#include <array>
#include <cstdint>

class Pawn
{
public:
  ~Pawn() = default;

  static void initialize();

	static std::array<std::uint64_t, 64> generateMoves(bool white);

	static std::array<std::uint64_t, 64> getWhiteMoves() { return whitePawnMoves; }

	static std::array<std::uint64_t, 64> getBlackMoves() { return blackPawnMoves; }

private:
	static std::array<std::uint64_t, 64> blackPawnMoves;
	static std::array<std::uint64_t, 64> whitePawnMoves;
};