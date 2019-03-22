#include <fstream>
#include <iostream>
#include <Board.hpp>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <io/MoveReader.h>
#include "../include/BoardMoveBenchmarks.h"

#define unlikely(x)     __builtin_expect((x),0)

void BoardMoveBenchmarks::benchmark(const std::string &testFile) {
	std::ifstream matchesFile(testFile);

	if (!matchesFile.is_open()) {
		std::cout << "The matches file for the benchmark could not be opened" << std::endl;
		return;
	}

	char promotionPiece = ' ';

	unsigned long moveNumber = 0, totalNumOfMoves = 0, matchNumber = 0;
	std::clock_t cpuCyclesUsed = 0;

	std::cout << "Benchmark is starting, this may take a while depending on the size of the benchmarking file..."
	          << std::endl;

	MoveReader moveReader(matchesFile);

	startWallTimer();

	while (!moveReader.finishedReading()) {
		Board board;

		if (showMatchesPlayed && matchNumber % 10000 == 0)
			std::cout << "\rMatches played: " << matchNumber << std::flush;

		std::string moveStr;
		while (!(moveStr = moveReader.readMove()).empty()) {
			const std::uint64_t startPos = (7u - (moveStr[0] - 97)) + (8 * (moveStr[1] - 49));
			const std::uint64_t endPos = (7u - (moveStr[2] - 97)) + (8 * (moveStr[3] - 49));
			if (unlikely(moveStr.length() == 5)) {
				promotionPiece = moveStr[4];
				if (promotionPiece >= 97)
					promotionPiece -= 32; // Make uppercase
			}

			startCPUTimer();
			board.makeMove(startPos, endPos, promotionPiece);
			stopCPUTimer();
			moveNumber++;
		}

		totalNumOfMoves += moveNumber;
		moveNumber = 0;
		matchNumber++;
	}

	stopWallTimer();

	std::cout << "Benchmark has finished running, " << matchNumber << " matches were played, " << totalNumOfMoves
	          << " moves" << std::endl;

	std::cout << getElapsedCPUCycles() << std::endl;
	const double cpuTimeInSecs = getElapsedCPUCycles() / (double) CLOCKS_PER_SEC;
	std::cout << "CPU time taken by board.makeMove() is: ";
	printFormattedRuntime(cpuTimeInSecs);

	std::cout << "Wall time taken to run benchmark: ";
	printFormattedRuntime(getElapsedWallSeconds());

	std::cout << "Avg moves per second: " << std::setprecision(4) << (totalNumOfMoves / cpuTimeInSecs) << std::endl;
}