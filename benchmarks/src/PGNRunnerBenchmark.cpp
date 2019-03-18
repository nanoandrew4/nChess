#include <fstream>
#include <iostream>
#include <Board.hpp>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "../include/PGNRunnerBenchmark.h"

#define unlikely(x)     __builtin_expect((x),0)

void PGNRunnerBenchmark::benchmark(const std::string &testFile) {
	std::ifstream matchesFile;
	matchesFile.open(testFile);

	if (!matchesFile.is_open()) {
		std::cout << "The matches file for the benchmark could not be opened" << std::endl;
		return;
	}

	std::uint64_t startPos, endPos, nextInput;
	char promotionPiece;

	unsigned long moveNumber = 0, totalNumOfMoves = 0, matchNumber = 0;
	double cpuCyclesUsed = 0;

	std::cout << "Benchmark is starting, this may take a while depending on the size of the benchmarking file..."
	          << std::endl;

	std::chrono::steady_clock::time_point startWallTime(std::chrono::steady_clock::now());
	while (!matchesFile.eof()) {
		Board board;
		nextInput = 0;

		if (showMatchesPlayed && matchNumber % 10000 == 0)
			std::cout << "\rMatches played: " << matchNumber << std::flush;

		while (nextInput != '|') { // TODO: maybe remove promotion piece from file and only react when it is present
			matchesFile >> startPos >> endPos >> nextInput;
			promotionPiece = ' ';
			if (unlikely(nextInput > 65))
				promotionPiece = nextInput;

			std::clock_t start_c = std::clock();
			board.makeMove(startPos, endPos, promotionPiece);
			cpuCyclesUsed += std::clock() - start_c;
			moveNumber++;
		}

		totalNumOfMoves += moveNumber;
		moveNumber = 0;
		matchNumber++;
	}

	std::chrono::steady_clock::time_point endWallTime(std::chrono::steady_clock::now());
	double runtime = std::chrono::duration_cast<std::chrono::duration<double>>(endWallTime - startWallTime).count();

	std::cout << "Benchmark has finished running, " << matchNumber << " matches were played, " << totalNumOfMoves
	          << " moves" << std::endl;

	const double cpuTimeInSecs = cpuCyclesUsed / CLOCKS_PER_SEC;
	std::cout << "CPU time taken by board.makeMove() is: ";
	printFormattedRuntime(cpuTimeInSecs);

	std::cout << "Wall time taken to run benchmark: ";
	printFormattedRuntime(runtime);

	std::cout << "Avg moves per second: " << std::setprecision(4) << (totalNumOfMoves / cpuTimeInSecs) << std::endl;
}

void PGNRunnerBenchmark::printFormattedRuntime(const double micros) {
	std::cout << (int) micros / 3600 << "h " << ((int) micros % 3600) / 60 << "m "
	          << (int) micros % 60 << "s " << (int) (micros * 1000.0) % 1000 << "ms"
	          << std::endl;
}
