#include <cstring>
#include "pieces/King.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Queen.hpp"
#include "io/UCIParser.hpp"
#include "../test/include/Test.h"
#include "../test/include/PieceMovesTest.h"
#include "../benchmarks/include/BoardMoveBenchmarks.h"
#include "../benchmarks/include/MoveReaderBenchmark.h"
#include <thread>

#ifdef __linux__

/**
 * Sets the main thread affinity to the last core available. If scripts/bench/hideLastCore has been run, it will
 * have limited all processes to run on all cores but the last, so this process should have the core all to itself.
 */
void setCPUAffinity() {
	cpu_set_t set;
	CPU_ZERO(&set);        // clear cpu mask
	CPU_SET(std::thread::hardware_concurrency() - 1, &set);      // set cpu 0
	sched_setaffinity(0, sizeof(cpu_set_t), &set);  // 0 is the calling process
}

#else
void setCPUAffinity() {}
#endif

void playMatch();

void runTests(int startArg, int numOfArgs, char *args[]);

void runBenchmark(int startArg, int numOfArgs, char *args[]);

bool strMatch(const char *orig, const std::string &target) {
	return strncmp(orig, target.data(), target.length()) == 0;
}

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

	for (int i = 1; i < argc; i++) {
		if (strMatch(argv[i], "test")) {
			runTests(i + 1, argc, argv);
			return 0;
		} else if (strMatch(argv[i], "bench")) {
			runBenchmark(i + 1, argc, argv);
			return 0;
		} else if (strMatch(argv[i], "play")) {
			playMatch();
			return 0;
		} else if (strMatch(argv[i], "--lastcore"))
			setCPUAffinity();
	}

	std::cout << "Use --help for options" << std::endl;

	return 0;
}

void runTests(int startArg, int numOfArgs, char *args[]) {
	unsigned long startMove = 0, startMatch = 0;
	std::string pathToFile;
	for (int i = startArg; i < numOfArgs; i += 2) {
		if (strMatch(args[i], "--smove"))
			startMove = std::stoul(args[i + 1]);
		else if (strMatch(args[i], "--smatch"))
			startMatch = std::stoul(args[i + 1]);
		else if (strMatch(args[i], "--path"))
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

void runBenchmark(int startArg, int numOfArgs, char *args[]) {
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);

	if (strMatch(args[startArg], "move")) {
		BoardMoveBenchmarks benchmark;
		benchmark.benchmark(args[startArg + 1]);
	} else if (strMatch(args[startArg], "fileread")) {
		MoveReaderBenchmark benchmark;
		benchmark.benchmark(args[startArg + 1]);
	}
}

void playMatch() {
	Board b;
	while (!b.isMatchOver()) {
		b.displayBoard();
		std::string moveStr;
		std::array<char, 5> moveArr{};

		do {
			std::cout << "Player turn: " << (b.getCurrentTurn() % 2 == 0 ? "white" : "black") << std::endl;
			std::cout << "Current turn: " << b.getCurrentTurn() << std::endl;
			std::cout << "Enter move in UCI format: ";
			std::cin >> moveStr;
			for (int i = 0; i < moveStr.length() && i < moveArr.size(); i++)
				moveArr[i] = moveStr[i];
		} while (moveStr.length() < 4 || moveStr.length() > 5 || !UCIParser::parseAndMove(b, moveArr));
	}
}