#include "pieces/King.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Queen.hpp"
#include "UCIParser.hpp"

#include <iostream>

int main()
{
    std::cout << UCIParser::parse("e4h1") << std::endl;
}