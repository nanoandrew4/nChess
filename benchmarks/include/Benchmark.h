#ifndef NCHESS_BENCHMARK_H
#define NCHESS_BENCHMARK_H

#include <ctime>
#include <chrono>
#include <zconf.h>

class Benchmark {
public:
	void startWallTimer() { wallStart = std::chrono::steady_clock::now(); };

	void startNanoTimer() { cpuStart = std::chrono::high_resolution_clock::now(); };

	void stopNanoTimer() {
		elapsedNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - cpuStart).count();
	};

	void stopWallTimer() {
		elapsedWallSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(
				std::chrono::steady_clock::now() - wallStart).count();
	};

	void accumulateNanoTime() { accumulatedNanoseconds += elapsedNanoseconds; }

	void accumulateWallTime() { accumulatedWallSeconds += elapsedWallSeconds; }

	double getElapsedWallSeconds() const { return elapsedWallSeconds; }

	long getElapsedNanoseconds() const { return elapsedNanoseconds; }

	double getAccumulatedWallSeconds() const { return accumulatedWallSeconds; }

	long getAccumulatedCPUSeconds() const { return accumulatedNanoseconds; }

	static void printFormattedRuntime(const double secs) {
		std::cout << (int) secs / 3600 << "h " << ((int) secs % 3600) / 60 << "m "
		          << (int) secs % 60 << "s " << (int) (secs * 1000.0) % 1000 << "ms"
		          << std::endl;
	}

private:
	std::chrono::high_resolution_clock::time_point cpuStart;
	std::chrono::steady_clock::time_point wallStart;

	double elapsedWallSeconds = 0;
	long elapsedNanoseconds = 0;

	double accumulatedWallSeconds = 0;
	long accumulatedNanoseconds = 0;
};

#endif //NCHESS_BENCHMARK_H
