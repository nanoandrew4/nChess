#ifndef NCHESS_PGNRUNNERBENCHMARK_H
#define NCHESS_PGNRUNNERBENCHMARK_H

#include <string>
#include "Benchmark.h"

class BoardMoveBenchmarks : public Benchmark {
public:
	BoardMoveBenchmarks() = default;

	~BoardMoveBenchmarks() = default;

	void benchmark(const std::string &testFile);

	static constexpr bool showMatchesPlayed = true;
};


#endif //NCHESS_PGNRUNNERBENCHMARK_H
