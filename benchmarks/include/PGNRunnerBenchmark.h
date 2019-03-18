#ifndef NCHESS_PGNRUNNERBENCHMARK_H
#define NCHESS_PGNRUNNERBENCHMARK_H


#include <string>

class PGNRunnerBenchmark {
public:
	PGNRunnerBenchmark() = default;

	~PGNRunnerBenchmark() = default;

	void benchmark(const std::string &testFile);

	void printFormattedRuntime(double seconds);

	static constexpr bool showMatchesPlayed = true;
};


#endif //NCHESS_PGNRUNNERBENCHMARK_H
