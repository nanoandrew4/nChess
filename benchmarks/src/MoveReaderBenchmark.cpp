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

	std::cout << "Read file size is: " << (moveReader.getBytesRead()) / pow(1000.0, 3) << " GB" << std::endl;

	movesFile.close();
}
