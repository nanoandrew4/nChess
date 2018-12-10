#pragma once

#include <array>
#include <cstdlib>

class Rook
{

  public:
    Rook();
    ~Rook();

    void visDebug(int pos);

  private:
    std::array<std::uint64_t, 64> moves;

    void initializeMoves();
};