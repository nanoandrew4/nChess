#ifndef NCHESS_BENCHMARK_H
#define NCHESS_BENCHMARK_H

#include <ctime>
#include <chrono>
#include <zconf.h>

class Benchmark {
public:
	void startWallTimer() { wallStart = std::chrono::steady_clock::now(); };

	void startCPUTimer() { startCPUCycles = rdtsc(); };

	void stopCPUTimer() {
		elapsedCycles = rdtsc() - startCPUCycles;
	};

	void stopWallTimer() {
		elapsedWallSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(
				std::chrono::steady_clock::now() - wallStart).count();
	};

	void accumulateCPUCycles() { accumulatedCycles += elapsedCycles; }

	void accumulateWallTime() { accumulatedWallSeconds += elapsedWallSeconds; }

	double getElapsedWallSeconds() const { return elapsedWallSeconds; }

	long getElapsedCPUCycles() const { return elapsedCycles; }

	double getAccumulatedWallSeconds() const { return accumulatedWallSeconds; }

	long getAccumulatedCPUCycles() const { return accumulatedCycles; }

	static void printFormattedRuntime(const double secs) {
		std::cout << (int) secs / 3600 << "h " << ((int) secs % 3600) / 60 << "m "
		          << (int) secs % 60 << "s " << (int) (secs * 1000.0) % 1000 << "ms"
		          << std::endl;
	}

private:
	std::uint64_t startCPUCycles = 0;
	std::chrono::steady_clock::time_point wallStart;

	double elapsedWallSeconds = 0;
	std::uint64_t elapsedCycles = 0;

	double accumulatedWallSeconds = 0;
	std::uint64_t accumulatedCycles = 0;

	inline std::uint64_t rdtsc() {
		std::uint32_t low, high;
		asm volatile ("rdtsc" : "=a" (low), "=d" (high));
		return (std::uint64_t) high << 32ul | low;
	}
};

#endif //NCHESS_BENCHMARK_H
