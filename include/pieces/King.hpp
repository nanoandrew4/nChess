#pragma once

#include <array>
#include <cstdint>

class King
{
  public:
    ~King() = default;

    static void initialize();

	static std::array<std::uint64_t, 64> generateMoves(bool white);

	static void visDebug(bool white, unsigned long pos);

	static std::array<std::uint64_t, 64> getWhiteMoves() { return whiteMoves; }

	static std::array<std::uint64_t, 64> getBlackMoves() { return blackMoves; }

  private:
	static std::array<std::uint64_t, 64> whiteMoves;
	static std::array<std::uint64_t, 64> blackMoves;
};