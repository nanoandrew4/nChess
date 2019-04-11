#ifndef NCHESS_MOVEREADERBENCHMARK_H
#define NCHESS_MOVEREADERBENCHMARK_H


#include <string>
#include "Benchmark.h"

class MoveReaderBenchmark : public Benchmark {
public:
	void benchmark(const std::string &movesFilePath);

private:
	void printProcessedDataSize(unsigned long processedBytes);

	void printThroughput(unsigned long processedBytes, double processingTimeSecs);

	std::string getBytesSizeString(unsigned long processedBytes);
};

#endif //NCHESS_MOVEREADERBENCHMARK_H
