#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <chrono>

#define unlikely(x)     __builtin_expect((x),0)

/*
 * This code is a convenience script that converts UCI moves (e.g e2e4) to a format that the benchmarking classes
 * can understand, so that they may pass the input directly to the Board class without having to parse anything.
 * It essentially takes the UCIParser class and outputs the starting and ending positions, as well as the promotion
 * piece. If no promotion piece is to be had (pretty much always the case) a '_' is printed instead.
 */

bool isPromotionPiece(const char piece) {
	return piece == 'Q' || piece == 'R' || piece == 'B' || piece == 'N';
}

bool notColumn(char val) {
	return val < 97 || val > 104;
}

bool notRow(char val) {
	return val < 49 || val > 56;
}

bool parseAndOutput(const std::string &moveStr, std::ostream &output) {
	if (moveStr.length() < 4 || moveStr.length() > 5) {
		std::cout << "Move length is invalid" << std::endl;
		return false;
	} else if (moveStr.length() == 5 && !isPromotionPiece(moveStr[4])) {
		std::cout << "Promotion piece is invalid" << std::endl;
		return false;
	} else if (notColumn(moveStr[0]) || notColumn(moveStr[2]) || notRow(moveStr[1]) || notRow(moveStr[3])) {
		std::cout << "Entered move is invalid" << std::endl;
		return false;
	}

	const std::uint64_t startPos = (7 - (moveStr[0] - 97)) + (8 * (moveStr[1] - 49));
	const std::uint64_t endPos = (7 - (moveStr[2] - 97)) + (8 * (moveStr[3] - 49));
	char promotionPiece = ' ';
	if (moveStr.length() == 5) {
		promotionPiece = moveStr[4];
		if (promotionPiece >= 97)
			promotionPiece -= 32; // Make uppercase
	}

	output << startPos << " " << endPos << " ";
	if (unlikely(promotionPiece != ' '))
		output << promotionPiece << " ";
	return true;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Usage: UCIFileConverter [inputFileName] [outputFileName]" << std::endl;
		return 1;
	}

	std::ifstream pgnFile;
	pgnFile.open(argv[1]);

	std::ofstream outputFile(argv[2]);
	std::string line, move;
	const std::string delimiter = " ";
	std::size_t pos = 0;

	unsigned long moveNumber = 0, matchNumber = 0, totalNumOfMoves = 0;

	auto start = std::chrono::high_resolution_clock::now();

	while (std::getline(pgnFile, line)) {
		if (matchNumber % 10000 == 0 && matchNumber > 0)
			std::cout << "\rParsed matches: " << matchNumber << std::flush;

		while ((pos = line.find(delimiter)) != std::string::npos) {
			move = line.substr(0, pos);
			if (!parseAndOutput(move, outputFile))
				std::cout << std::endl << "An error ocurred while parsing match/movement: " << matchNumber << "/"
				          << moveNumber << std::endl;
			line.erase(0, pos + delimiter.length());
			moveNumber++;
		}

		totalNumOfMoves += moveNumber;
		moveNumber = 0;
		matchNumber++;
		outputFile << "|\n";
	}

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long elapsedMicroSecs = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

	std::cout << std::endl << "Parsed " << matchNumber << " matches containing " << totalNumOfMoves << " moves in "
	          << elapsedMicroSecs / 1000000.0 << "s" << std::endl;

	pgnFile.close();
	outputFile.close();
}
