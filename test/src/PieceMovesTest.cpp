#include <UCIParser.hpp>
#include "../include/PieceMovesTest.h"

#include <fstream>
#include <chrono>

void PieceMovesTest::test() {
	std::ifstream pgnFile;
	pgnFile.open(PieceMovesTest::pathToTestFile);

	if (!pgnFile.is_open()) {
		std::cout << "Error opening test file for test class PieceMovesTest, path to file is invalid or was not set" <<
		          std::endl;
		return;
	}

	std::string line;
	const std::string delimiter = " ";
	std::size_t pos = 0;

	bool stepping = startMatch != 0 || startMove != 0;
	std::string move;
	unsigned long totalMoves = 0;

	std::chrono::steady_clock::time_point start(std::chrono::steady_clock::now());
	while (std::getline(pgnFile, line)) {
		Board board;
		if (matchNumber % 10000 == 0 && matchNumber > 0)
			std::cout << "\rNumber of test matches completed: " << matchNumber << std::flush;

		while ((pos = line.find(delimiter)) != std::string::npos) {
			move = line.substr(0, pos);
			const bool moveSuccessful = makeMoveAndCheck(move, board);

			if (stepping && startMatch == matchNumber && moveNumber >= startMove) {
				std::cout << "Move played is: " << move << std::endl;
				std::cout << "Current match/move number: " << matchNumber << "/" << moveNumber << std::endl;
				board.displayBoard();
				std::cin.get();
				std::cin.get();
			}

			if (!stepping && !moveSuccessful)
				break;

			line.erase(0, pos + delimiter.length());
		}

		totalMoves += moveNumber;
		moveNumber = 0;
		matchNumber++;
	}

	pgnFile.close();

	std::chrono::steady_clock::time_point end(std::chrono::steady_clock::now());
	double runtime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "\rCompleted testing of " << matchNumber << " matches in " << (int) runtime / 3600 << "h "
	          << ((int) runtime % 3600) / 60 << "m " << (int) runtime % 60 << "s " << (int) (runtime * 1000.0) % 1000
	          << "ms"
	          << std::endl;

	std::cout << "Number of moves evaluated: " << totalMoves << std::endl;

	std::cout << std::endl;
}

bool PieceMovesTest::makeMoveAndCheck(const std::string &move, Board &board) {
	const std::vector<std::uint64_t> setGlobalBitsBeforeMove = Board::getSetBits(board.getGlobalBB());

	const std::uint64_t startPos = (7 - (move[0] - 97)) + (8 * (move[1] - 49));
	const std::uint64_t endPos = (7 - (move[2] - 97)) + (8 * (move[3] - 49));
	const bool capture = (((std::uint64_t) 1 << endPos) & board.getGlobalBB()) != 0;

	const bool movementSuccessful = UCIParser::parse(board, move);

	const std::vector<std::uint64_t> setBits = Board::getSetBits(board.getGlobalBB());
	bool startPosUnset = true, endPosSet = false;
	for (std::uint64_t bitPos : setBits) {
		if (bitPos == startPos)
			startPosUnset = false;
		else if (bitPos == endPos)
			endPosSet = true;
	}

	const unsigned long prevSize = getNumOfTestFailures();
	if (!movementSuccessful)
		logTestFailure(TestFailData("PieceMovesTest", genFailedToMakeMoveErrorMessage()));
	if (!startPosUnset)
		logTestFailure(TestFailData("PieceMovesTest", genFailedToRemoveErrorMessage()));
	if (!endPosSet)
		logTestFailure(TestFailData("PieceMovesTest", genFailedToMoveErrorMessage()));
	if (capture && setGlobalBitsBeforeMove.size() != setBits.size() + 1)
		logTestFailure(TestFailData("PieceMovesTest", genFailedToRemoveCapturedPieceErrorMessage()));

	if (getNumOfTestFailures() != prevSize) {
		std::cout << "The current test failed... The following move was attempted: " << move
		          << " and was at match/move number: " << matchNumber << "/" << moveNumber << std::endl;
		board.displayBoard();
	}
	moveNumber++;

	return movementSuccessful;
}

std::string PieceMovesTest::genFailedToRemoveErrorMessage() const {
	return "Failed to delete piece from starting position at turn: " + std::to_string(matchNumber) + "/" +
	       std::to_string(moveNumber);
}

std::string PieceMovesTest::genFailedToMoveErrorMessage() const {
	return "Failed to move piece to target position at turn: " + std::to_string(matchNumber) + "/" +
	       std::to_string(moveNumber);
}

std::string PieceMovesTest::genFailedToRemoveCapturedPieceErrorMessage() const {
	return "Failed to remove captured piece at match/turn: " + std::to_string(matchNumber) + "/" +
	       std::to_string(moveNumber);
}

std::string PieceMovesTest::genFailedToMakeMoveErrorMessage() const {
	return "Failed to make move at turn: " + std::to_string(matchNumber) + "/" +
	       std::to_string(moveNumber);
}
