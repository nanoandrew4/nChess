#ifndef NCHESS_MOVEREADERBENCHMARK_H
#define NCHESS_MOVEREADERBENCHMARK_H


#include <string>
#include "Benchmark.h"

class MoveReaderBenchmark : public Benchmark {
public:
	/**
	 * Benchmarks the speed at which the specified file is read and converted to the inputs for nChess.
	 */
	void benchmark(const std::string &movesFilePath);

private:
#ifdef VISUAL_BECHMARK
	static constexpr bool visualBenchmark = true;
#else
	static constexpr bool visualBenchmark = false;
#endif

	/**
	 * Prints the number of bytes supplied in an easy to read format, e.g x GB.
	 *
	 * @param processedBytes Number of processed bytes
	 */
	void printProcessedDataSize(unsigned long processedBytes);

	/**
	 * Prints the speed at which data is read from disk and converted to a format suitable for nChess functions.
	 *
	 * @param processedBytes Number of bytes that were read and converted
	 * @param processingTimeSecs Number of seconds it took to read and process the aforementioned bytes
	 */
	void printThroughput(unsigned long processedBytes, double processingTimeSecs);

	/**
	 * Returns a string to represent the number of bytes in a more readable format (e.g MB or GB).
	 *
	 * @param processedBytes Number of bytes for which to return the appropriate size descriptor string
	 * @return Size descriptor appropriate for the number of processed bytes (e.g MB or GB)
	 */
	std::string getBytesSizeString(unsigned long processedBytes);
};

#endif //NCHESS_MOVEREADERBENCHMARK_H
