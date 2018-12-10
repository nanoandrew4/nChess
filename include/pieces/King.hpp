#pragma once

#include <array>
#include <cstdint>

class King {

public:
    King();
    ~King();

    void visDebug(int pos);
private:
    std::array<std::uint64_t, 64> moves;

    void initializeMoves();
};