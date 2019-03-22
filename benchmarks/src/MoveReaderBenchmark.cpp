#include <fstream>
#include <io/MoveReader.h>
#include <iostream>
#include "../include/MoveReaderBenchmark.h"

void MoveReaderBenchmark::benchmark(const std::string &movesFilePath) {
	std::ifstream movesFile(movesFilePath);

	std::cout << "Starting file processing benchmark... " << std::endl;

	MoveReader moveReader(movesFile);
	startWallTimer();
	while (!movesFile.eof())
		moveReader.readMove();
	stopWallTimer();

	std::cout << "Finished benchmark, file read took: " << std::endl;
	std::cout << "File size in bytes is: " << moveReader.getBytesRead() << std::endl;

	movesFile.close();
}
