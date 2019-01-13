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

    Board b;
    while (true)
    {
        b.displayBoard();
        std::string move;

        do
        {
            std::cout << "Player turn: " << (b.getCurrentTurn() % 2 == 0 ? "white" : "black") << std::endl;
            std::cout << "Current turn: " << b.getCurrentTurn() << std::endl;
            std::cout << "Enter move in UCI format: ";
            std::cin >> move;
        } while (!UCIParser::parse(b, move));
    }
}