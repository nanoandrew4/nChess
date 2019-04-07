#ifndef NCHESS_PGNRUNNERBENCHMARK_H
#define NCHESS_PGNRUNNERBENCHMARK_H

#include <string>
#include "Benchmark.h"

class BoardMoveBenchmarks : public Benchmark {
public:
	BoardMoveBenchmarks() = default;

	~BoardMoveBenchmarks() = default;

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

	void printMetrics();
	void runBenchmark(std::ifstream &stream);
};


#endif //NCHESS_PGNRUNNERBENCHMARK_H
