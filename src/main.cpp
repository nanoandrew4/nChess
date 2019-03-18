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
#include "../benchmarks/include/PGNRunnerBenchmark.h"

void playMatch();

void runTests(int numOfArgs, char *args[]);

void runBenchmark(int numOfArgs, char *args[]);

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

	if (argc > 1 && strncmp(argv[1], "test", 4) == 0)
		runTests(argc, argv);
	else if (argc == 3 && strncmp(argv[1], "bench", 5) == 0)
		runBenchmark(argc, argv);
	else
		playMatch();

	return 0;
}

void runTests(int numOfArgs, char *args[]) {
	unsigned long startMove = 0, startMatch = 0;
	std::string pathToFile;
	for (int i = 2; i < numOfArgs; i += 2) {
		const std::string arg = args[i];
		if (strncmp(args[i], "--smove", 7) == 0)
			startMove = std::stoul(args[i + 1]);
		else if (strncmp(args[i], "--smatch", 8) == 0)
			startMatch = std::stoul(args[i + 1]);
		else if (strncmp(args[i], "--path", 6) == 0)
			pathToFile = args[i + 1];
	}

	Test::startTests();

	PieceMovesTest pieceMovesTest;
	pieceMovesTest.setPathToTestFile(pathToFile);
	pieceMovesTest.setStartMatch(startMatch);
	pieceMovesTest.setStartMove(startMove);
	pieceMovesTest.run();

	Test::stopTests();
}

void runBenchmark(int numOfArgs, char *args[]) {
	PGNRunnerBenchmark benchmark;

	const std::string pathToBenchMatches;
	benchmark.benchmark(args[2]);
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