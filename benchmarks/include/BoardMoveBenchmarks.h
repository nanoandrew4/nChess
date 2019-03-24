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
	long maxMoveTime = 0;
	long minMoveTime = 1u << 31u;

	void printMetrics();

	void runBenchmark(std::ifstream &stream);

	void printTimePerMove(std::string preTimeText, double avgTimePerMove);

	std::string getSubsecondTimeUnit(double secs);
};


#endif //NCHESS_PGNRUNNERBENCHMARK_H
