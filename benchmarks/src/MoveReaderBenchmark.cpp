#include <fstream>
#include <io/MoveReader.h>
#include <iostream>
#include <cmath>
#include "../include/MoveReaderBenchmark.h"

void MoveReaderBenchmark::benchmark(const std::string &movesFilePath) {
	std::ifstream movesFile(movesFilePath);

	if (!movesFile.is_open()) {
		std::cout << "Error opening the testing file" << std::endl;
		return;
	}

	std::cout << "Starting file processing benchmark... " << std::endl;

	MoveReader moveReader(movesFile);
	startWallTimer();
	while (!moveReader.finishedReading())
		moveReader.readMove();
	stopWallTimer();

	std::cout << "Finished benchmark, file read took: ";
	printFormattedRuntime(getElapsedWallSeconds());

	printProcessedDataSize(moveReader.getBytesRead());
	printThroughput(moveReader.getBytesRead(), getElapsedWallSeconds());

	movesFile.close();
}

void MoveReaderBenchmark::printProcessedDataSize(unsigned long processedBytes) {
	double processedDataSize = processedBytes;
	while (processedDataSize > 1000)
		processedDataSize /= 1000.0;

	std::cout << "Read file size is: " << processedDataSize << " " << getBytesSizeString(processedBytes)
	          << std::endl;
}

void MoveReaderBenchmark::printThroughput(unsigned long processedBytes, double processingTimeSecs) {
	double throughput = processedBytes / processingTimeSecs;
	while (throughput > 1000.0)
		throughput /= 1000.0;

	std::cout << "Throughput is: " << throughput << " "
	          << getBytesSizeString(static_cast<unsigned long>(processedBytes / processingTimeSecs)) << "/s"
	          << std::endl;
}

std::string MoveReaderBenchmark::getBytesSizeString(unsigned long processedBytes) {
	if (processedBytes < 1000)
		return "B";
	else if (processedBytes / 1000 < 1000)
		return "kB";
	else if (processedBytes / 1000 < 1000000)
		return "MB";
	else if (processedBytes / 1000000 < 1000000)
		return "GB";
	else
		return "??";
}
