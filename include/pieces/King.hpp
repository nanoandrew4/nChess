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

  private:
    static std::array<std::uint64_t, 64> moves;
};