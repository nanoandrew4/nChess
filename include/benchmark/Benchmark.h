#ifndef NCHESS_BENCHMARK_H
#define NCHESS_BENCHMARK_H

#include <ctime>
#include <chrono>
#include <zconf.h>
#include <iostream>

class Benchmark {
public:
	/**
	 * Starts counting the wall clock time from the point this function is called until stopWallTimer() is called.
	 */
	void startWallTimer() { wallStart = std::chrono::steady_clock::now(); };

	/**
	 * Starts counting the elapsed CPU cycles from the point this function is called until stopCPUTimer() is called.
	 */
	void startCPUTimer() { startCPUCycles = rdtsc(); };

	/**
	 * Stops the CPU timer and stores the number of CPU cycles since startCPUTimer() was called in 'elapsedCycles'.
	 */
	void stopCPUTimer() {
		elapsedCycles = rdtsc() - startCPUCycles;
	};

	/**
	 * Stops the wall timer and stores the time difference since startWallTimer() was called in 'elapsedWalLSeconds'.
	 */
	void stopWallTimer() {
		elapsedWallSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(
				std::chrono::steady_clock::now() - wallStart).count();
	};

	/**
	 * Accumulates the elapsed CPU cycles in 'accumulatedCycles'. stopCPUTimer() should be called prior to this
	 * function.
	 */
	void accumulateCPUCycles() { accumulatedCycles += elapsedCycles; }

	/**
	 * Accumulates the elapsed time in 'accumulatedWallSeconds'. stopWallTimer() should be called prior to this
	 * function.
	 */
	void accumulateWallTime() { accumulatedWallSeconds += elapsedWallSeconds; }

	/**
	 * Returns the number of seconds between the startWallTimer() and stopWallTimer() function calls.
	 *
	 * @return Elapsed seconds between starting and stopping the wall timer
	 */
	double getElapsedWallSeconds() const { return elapsedWallSeconds; }

	/**
	 * Returns the number of CPU cycles between the startCPUTimer() and stopCPUTimer() function calls.
	 *
	 * @return Elapsed CPU cycles between starting and stopping the wall timer
	 */
	long getElapsedCPUCycles() const { return elapsedCycles; }

	/**
	 * Returns the number of accumulated seconds from calls to accumulateWallTime().
	 *
	 * @return Number of accumulated seconds
	 */
	double getAccumulatedWallSeconds() const { return accumulatedWallSeconds; }

	/**
	 * Returns the number of accumulated CPU cycles from calls to accumulateCPUCyles().
	 *
	 * @return Number of accumulated CPU cycles
	 */
	long getAccumulatedCPUCycles() const { return accumulatedCycles; }

	/**
	 * Prints the supplied seconds in a hh:MM::ss:SSS format.
	 *
	 * @param secs Number of seconds to display as formatted time
	 */
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

	/**
	 * Returns the number of cycles stored in the RDTSC register (which should represent the CPU cycles since the
	 * core was started, on modern processors).
	 *
	 * @return Number of CPU cycles elapsed since the core was started, or since the BIOS was reset (on older
	 * processors)
	 */
	inline std::uint64_t rdtsc() {
		std::uint32_t low, high;
		asm volatile ("rdtsc" : "=a" (low), "=d" (high));
		return (std::uint64_t) high << 32ul | low;
	}
};

#endif //NCHESS_BENCHMARK_H
