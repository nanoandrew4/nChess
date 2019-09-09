#include <fstream>
#include <iostream>
#include <Board.hpp>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <io/MoveReader.h>
#include <cmath>
#include "benchmark/BoardMoveBenchmarks.h"

void BoardMoveBenchmarks::benchmark(const std::string &testFile) {
	std::ifstream matchesFile(testFile);

	if (!matchesFile.is_open()) {
		std::cout << "The matches file for the benchmark could not be opened" << std::endl;
		return;
	}

	if (visualBenchmark)
		std::cout << "Benchmark is starting, this may take a while depending on the size of the benchmarking file..."
		          << std::endl;

	if (visualBenchmark)
		startWallTimer();
	runBenchmark(matchesFile);
	if (visualBenchmark) {
		stopWallTimer();

		std::cout << "\rBenchmark has finished running, " << matchNumber << " matches were played, " << totalNumOfMoves
		          << " moves" << std::endl;

		printMetrics();
	}
}

void BoardMoveBenchmarks::runBenchmark(std::ifstream &stream) {
	MoveReader moveReader(stream);

	while (!moveReader.finishedReading()) {
		Board board;
		char promotionPiece = ' ';

		if (matchNumber % 100000 == 0 && visualBenchmark)
			std::cout << "\rMatches played: " << matchNumber << std::flush;

		std::array<char, 5> move{};
		while ((move = moveReader.readMove())[0] != '\0') {
			const std::uint64_t startPos = (7u - (move[0] - 97)) + (8 * (move[1] - 49));
			const std::uint64_t endPos = (7u - (move[2] - 97)) + (8 * (move[3] - 49));
			if (move[4] != '\0') {
				promotionPiece = move[4];
				if (promotionPiece >= 97)
					promotionPiece -= 32; // Make uppercase
			}

			if (visualBenchmark)
				startCPUTimer();
			const bool legal = board.makeMove(startPos, endPos, promotionPiece);
			if (__glibc_unlikely(!legal)) {
				std::cout << "Move that was illegal: " << startPos << " to " << endPos << std::endl;
				board.displayBoard();
				return;
			}
			if (visualBenchmark) {
				stopCPUTimer();
				accumulateCPUCycles();

				if (getElapsedCPUCycles() < minMoveCycles)
					minMoveCycles = getElapsedCPUCycles();
				if (getElapsedCPUCycles() > maxMoveCycles)
					maxMoveCycles = getElapsedCPUCycles();
				moveNumber++;
			}
		}

		totalNumOfMoves += moveNumber;
		moveNumber = 0;
		matchNumber++;
	}
}

void BoardMoveBenchmarks::printMetrics() {
	std::cout << "Wall time taken to run benchmark: ";
	printFormattedRuntime(getElapsedWallSeconds());

	std::cout << "CPU cycles taken by board.makeMove() are: " << getAccumulatedCPUCycles() / pow(10, 9) << " billion"
	          << std::endl;
	std::cout << "Avg CPU cycles per move: " << getAccumulatedCPUCycles() / static_cast<double>(totalNumOfMoves)
	          << std::endl;
	std::cout << "Min CPU cycles per move: " << minMoveCycles << std::endl;
	std::cout << "Max CPU cycles per move: " << maxMoveCycles << std::endl;
}