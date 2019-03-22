#include <fstream>
#include <io/MoveReader.h>
#include <iostream>
#include "../include/MoveReaderBenchmark.h"

void MoveReaderBenchmark::benchmark(const std::string &movesFilePath) {
	std::ifstream movesFile(movesFilePath);

	MoveReader moveReader(movesFile);
	startWallTimer();
	while (!movesFile.eof()) {
		moveReader.readMove();
	}
	stopCPUTimer();

	std::cout << "File read took: " << std::endl;
}
