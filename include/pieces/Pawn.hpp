#pragma once

#include <array>
#include <cstdint>

class Pawn
{
public:
  ~Pawn() = default;

  static void initialize();
  static std::array<std::uint64_t, 48> generateMoves(bool white);
  static void visDebug(int pos, bool white);

private:
  static std::array<std::uint64_t, 48> blackMoves;
  static std::array<std::uint64_t, 48> whiteMoves;
};