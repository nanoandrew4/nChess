#ifndef NCHESS_MOVEREADERBENCHMARK_H
#define NCHESS_MOVEREADERBENCHMARK_H


#include <string>
#include "Benchmark.h"

class MoveReaderBenchmark : public Benchmark {
	void benchmark(const std::string &movesFilePath);
};

#endif //NCHESS_MOVEREADERBENCHMARK_H
