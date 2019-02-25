#include "pieces/King.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Queen.hpp"
#include "UCIParser.hpp"
#include "../test/include/Test.h"
#include "../test/include/PieceMovesTest.h"

void playMatch();

void integrityTests();

void initBitBoards()
{
	Pawn::initialize();
	Rook::initialize();
	Knight::initialize();
	Bishop::initialize();
	Queen::initialize();
	King::initialize();
}

int main()
{
	initBitBoards();


	std::cout << "Welcome to nChess!" << std::endl << std::endl;
	std::cout << "1. Play a match" << std::endl;
	std::cout << "2. Check engine legality check integrity" << std::endl;

	int opt;
	do {
		std::cout << ">> ";
		std::cin >> opt;
	} while (opt < 1 || opt > 2);

	if (opt == 1)
		playMatch();
	else if (opt == 2)
		integrityTests();
}

void playMatch() {
	Board b;
	while (!b.isMatchOver()) {
		b.displayBoard();
		std::string move;

		do {
			std::cout << "Player turn: " << (b.getCurrentTurn() % 2 == 0 ? "white" : "black") << std::endl;
			std::cout << "Current turn: " << b.getCurrentTurn() << std::endl;
			std::cout << "Enter move in UCI format: ";
			std::cin >> move;
		} while (!UCIParser::parse(b, move));
	}
}

void integrityTests() {
	Test::startTests();

	PieceMovesTest pieceMovesTest;
	pieceMovesTest.run();

	Test::stopTests();
}