#include <fstream>
#include <iostream>
#include <Board.hpp>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <io/MoveReader.h>
#include <cmath>
#include "../include/BoardMoveBenchmarks.h"

void BoardMoveBenchmarks::benchmark(const std::string &testFile) {
	std::ifstream matchesFile(testFile);

	if (!matchesFile.is_open()) {
		std::cout << "The matches file for the benchmark could not be opened" << std::endl;
		return;
	}

	std::cout << "Benchmark is starting, this may take a while depending on the size of the benchmarking file..."
	          << std::endl;

	startWallTimer();
	runBenchmark(matchesFile);
	stopWallTimer();

	std::cout << "\rBenchmark has finished running, " << matchNumber << " matches were played, " << totalNumOfMoves
	          << " moves" << std::endl;

	printMetrics();
}

void BoardMoveBenchmarks::runBenchmark(std::ifstream &stream) {
	MoveReader moveReader(stream);

	while (!moveReader.finishedReading()) {
		Board board;
		char promotionPiece = ' ';

		if (matchNumber % 10000 == 0)
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

			startNanoTimer();
			board.makeMove(startPos, endPos, promotionPiece);
			stopNanoTimer();
			accumulateNanoTime();

			if (getElapsedNanoseconds() < minMoveTime)
				minMoveTime = getElapsedNanoseconds();
			if (getElapsedNanoseconds() > maxMoveTime)
				maxMoveTime = getElapsedNanoseconds();
			moveNumber++;
		}

		totalNumOfMoves += moveNumber;
		moveNumber = 0;
		matchNumber++;
	}
}

void BoardMoveBenchmarks::printMetrics() {
	const double cpuTimeInSecs = getAccumulatedCPUSeconds() / pow(10, 9);
	std::cout << "CPU time taken by board.makeMove() is: ";
	printFormattedRuntime(cpuTimeInSecs);

	std::cout << "Wall time taken to run benchmark: ";
	printFormattedRuntime(getElapsedWallSeconds());

	printTimePerMove("Avg time per move: ", cpuTimeInSecs / totalNumOfMoves);
	printTimePerMove("Lowest move time: ", minMoveTime / pow(10, 9));
	printTimePerMove("Highest move time: ", maxMoveTime / pow(10, 9));
}

void BoardMoveBenchmarks::printTimePerMove(std::string preTimeText, double avgTimePerMove) {
	double normalizedTimePerMove = avgTimePerMove;
	while (normalizedTimePerMove < 1.0 && normalizedTimePerMove != 0.0)
		normalizedTimePerMove *= 1000;

	std::cout << preTimeText << normalizedTimePerMove << " " << getSubsecondTimeUnit(avgTimePerMove)
	          << std::endl;
}

std::string BoardMoveBenchmarks::getSubsecondTimeUnit(double secs) {
	if (secs * pow(10, 3) > 1.0)
		return "ms";
	else if (secs * pow(10, 6) > 1.0)
		return "us";
	else if (secs * pow(10, 9) > 1.0)
		return "ns";
	else
		return "??";
}