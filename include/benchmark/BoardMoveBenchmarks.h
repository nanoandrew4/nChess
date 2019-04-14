#ifndef NCHESS_PGNRUNNERBENCHMARK_H
#define NCHESS_PGNRUNNERBENCHMARK_H

#include <string>
#include "Benchmark.h"

class BoardMoveBenchmarks : public Benchmark {
public:
	/**
	 * Benchmarks the speed at which nChess can check the legality of moves and perform them on a board.
	 * Uses runBenchmark() underneath, and also prints progress data to stdout.
	 *
	 * @param testFile File from which to read moves to evaluate
	 */
	void benchmark(const std::string &testFile);

private:
	unsigned long moveNumber = 0, totalNumOfMoves = 0, matchNumber = 0;
	long maxMoveCycles = 0;
	long minMoveCycles = 1UL << 31UL;

#ifdef VISUAL_BECHMARK
	static constexpr bool visualBenchmark = true;
#else
	static constexpr bool visualBenchmark = false;
#endif

	/**
	 * Prints metrics collected during the benchmarking phase to stdout, such as number of moves/matches evaluated
	 * and the average speed of each evaluation.
	 */
	void printMetrics();

	/**
	 * Runs the benchmark move evaluation benchmark, as described in the benchmark() function. Basically calls
	 * Board.makeMove() for each of the moves in the supplied file, while measuring the number of CPU cycles the
	 * evaluation takes.
	 *
	 * @param stream Input stream opened from the file containing the moves to benchmark with
	 */
	void runBenchmark(std::ifstream &stream);
};


#endif //NCHESS_PGNRUNNERBENCHMARK_H
