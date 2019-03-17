#include <cstring>
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

void initBitBoards() {
	Pawn::initialize();
	Rook::initialize();
	Knight::initialize();
	Bishop::initialize();
	Queen::initialize();
	King::initialize();
}

int main(int argc, char *argv[]) {
	initBitBoards();

	if (argc < 2) {
		std::cout << "Missing arguments" << std::endl;
		return 1;
	}

	if (argc > 1 && strncmp(argv[1], "test", 4) == 0) {
		unsigned long startMove = 0, startMatch = 0;
		std::string pathToFile;
		for (int i = 2; i < argc; i += 2) {
			const std::string arg = argv[i];
			if (strncmp(argv[i], "--smove", 7) == 0)
				startMove = std::stoul(argv[i + 1]);
			else if (strncmp(argv[i], "--smatch", 8) == 0)
				startMatch = std::stoul(argv[i + 1]);
			else if (strncmp(argv[i], "--path", 6) == 0)
				pathToFile = argv[i + 1];
		}

		Test::startTests();

		PieceMovesTest pieceMovesTest;
		pieceMovesTest.setPathToTestFile(pathToFile);
		pieceMovesTest.setStartMatch(startMatch);
		pieceMovesTest.setStartMove(startMove);
		pieceMovesTest.run();

		Test::stopTests();
	} else
		playMatch();

	return 0;
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