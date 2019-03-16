#include <UCIParser.hpp>
#include "../include/PieceMovesTest.h"

#include <fstream>

PieceMovesTest::PieceMovesTest() {
	std::cout << "Please input the path to the UCI pgn file, or enter 'd' to use default: ";
	std::cin >> pathToTestFile;

	if (pathToTestFile == "d")
		pathToTestFile = "/home/nanoandrew4/CLionProjects/nChess/KarpovUCIclean.pgn";
}

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

	std::cout << "Enter the move number you wish to start from: ";
	std::cin >> startMove;

	bool stepping = startMove != 0;
	unsigned long matchNumber = 0;
	std::string move;

	while (std::getline(pgnFile, line)) {
		if (matchNumber % 100 == 0)
			std::cout << "Number of test matches completed: " << matchNumber << std::endl;

		while ((pos = line.find(delimiter)) != std::string::npos) {
			move = line.substr(0, pos);
			makeMoveAndCheck(move);

			if (stepping && moveNumber >= startMove) {
				std::cout << "Move played is: " << move << std::endl;
				std::cout << "Current move number: " << moveNumber << std::endl;
				board.displayBoard();
				std::cin.get();
				std::cin.get();
			}

//			if (moveNumber > 20)
//				return;

			line.erase(0, pos + delimiter.length());
		}
		matchNumber++;
		board = Board();
	}
}

void PieceMovesTest::makeMoveAndCheck(const std::string &move) {
	const std::vector<std::uint64_t> setBitsBeforeMove = Board::getSetBits(board.getGlobalBB());

	const std::uint64_t startPos = (7 - (move[0] - 97)) + (8 * (move[1] - 49));
	const std::uint64_t endPos = (7 - (move[2] - 97)) + (8 * (move[3] - 49));
	const bool capture = (((std::uint64_t) 1 << endPos) & board.getGlobalBB()) != 0;
	char promotionPiece = ' ';
	if (move.length() == 5) {
		promotionPiece = move[4];
		if (promotionPiece >= 97)
			promotionPiece -= 32; // Make uppercase
	}

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
	if (capture && setBitsBeforeMove.size() != setBits.size() + 1)
		logTestFailure(TestFailData("PieceMovesTest", genFailedToRemoveCapturedPieceErrorMessage()));
	if (UCIParser::isPromotionPiece(promotionPiece) && setBitsBeforeMove.size() + 1 != setBits.size())
		logTestFailure(TestFailData("PieceMovesTest", genFailedToPromoteErrorMessage()));

	if (getNumOfTestFailures() != prevSize) {
		std::cout << "The current test failed... The following move was attempted on the current board: " << move
		          << " and was at move number: " << moveNumber << std::endl;
		board.displayBoard();
		std::cin.get();
		std::cin.get();
	}

	moveNumber++;
}

std::string PieceMovesTest::genFailedToRemoveErrorMessage() const {
	return "Failed to delete piece from starting position at turn: " + std::to_string(moveNumber);
}

std::string PieceMovesTest::genFailedToMoveErrorMessage() const {
	return "Failed to move piece to target position at turn: " + std::to_string(moveNumber);
}

std::string PieceMovesTest::genFailedToRemoveCapturedPieceErrorMessage() const {
	return "Failed to remove captured piece at turn: " + std::to_string(moveNumber);
}

std::string PieceMovesTest::genFailedToPromoteErrorMessage() const {
	return "Failed to promote piece at turn: " + std::to_string(moveNumber);
}

std::string PieceMovesTest::genFailedToMakeMoveErrorMessage() const {
	return "Failed to make move at turn: " + std::to_string(moveNumber);
}
