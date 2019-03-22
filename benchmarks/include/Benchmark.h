#ifndef NCHESS_BENCHMARK_H
#define NCHESS_BENCHMARK_H

#include <ctime>
#include <chrono>

class Benchmark {
public:
	void resetWallTimer() { elapsedWallSeconds = 0; }

	void resetCPUTimer() { elapsedCPUCycles = 0; }

	void startWallTimer() { wallStart = std::chrono::steady_clock::now(); };

	void startCPUTimer() { cpuStart = std::clock(); };

	void stopWallTimer() { elapsedCPUCycles += std::clock() - cpuStart; };

	void stopCPUTimer() {
		elapsedWallSeconds += std::chrono::duration_cast<std::chrono::duration<double>>(
				std::chrono::steady_clock::now() - wallStart).count();
	};

	double getElapsedWallSeconds() { return elapsedWallSeconds; }

	std::clock_t getElapsedCPUCycles() { return elapsedCPUCycles; }

	static void printFormattedRuntime(const double secs) {
		std::cout << (int) secs / 3600 << "h " << ((int) secs % 3600) / 60 << "m "
		          << (int) secs % 60 << "s " << (int) (secs * 1000.0) % 1000 << "ms"
		          << std::endl;
	}

private:
	std::clock_t cpuStart;
	std::chrono::steady_clock::time_point wallStart;

	double elapsedWallSeconds;
	std::clock_t elapsedCPUCycles;
};

#endif //NCHESS_BENCHMARK_H
