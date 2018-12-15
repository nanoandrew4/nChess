#include "Board.hpp"

#include <bitset>
#include <string>
#include <iostream>

Board::Board() {

}

Board::~Board() {

}

void Board::visDebug(std::uint64_t board) {
    std::string str = std::bitset<64>(board).to_string();

    for (int j = 0; j < 64; ++j) {
        if (j > 0 && j % 8 == 0)
            std::cout << std::endl;
        std::cout << str[j];
    }
    std::cout << std::endl << std::endl;
}

std::vector<int> Board::getSetBits(std::uint64_t val)
{
    std::vector<int> setBits;
    for (int i = 0; i < 64; ++i)
        if ((val & (val << i)) != 0)
            setBits.push_back(i);
    return setBits;
}