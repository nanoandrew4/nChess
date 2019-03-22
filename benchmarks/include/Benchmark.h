#ifndef NCHESS_BENCHMARK_H
#define NCHESS_BENCHMARK_H

#include <ctime>
#include <chrono>

class Benchmark {
public:
	void startWallTimer() { wallStart = std::chrono::steady_clock::now(); };

	void startCPUTimer() { cpuStart = std::clock(); };

	void stopWallTimer() { elapsedSeconds = (double) (std::clock() - cpuStart) / CLOCKS_PER_SEC; };

	void stopCPUTimer() {
		elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(
				std::chrono::steady_clock::now() - wallStart).count();
	};

	double getElapsedSeconds() { return elapsedSeconds; }

private:
	std::clock_t cpuStart;
	std::chrono::steady_clock::time_point wallStart;

	double elapsedSeconds;
};

#endif //NCHESS_BENCHMARK_H
