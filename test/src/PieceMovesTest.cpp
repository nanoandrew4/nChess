#include <UCIParser.hpp>
#include "../include/PieceMovesTest.h"

#include <fstream>

void PieceMovesTest::test() {
	std::ifstream pgnFile;
	pgnFile.open(pathToTestFile);

	if (!pgnFile.is_open()) {
		std::cout << "Error opening test file for test class PieceMovesTest, path to file is invalid or was not set" <<
		          std::endl;
		return;
	}

	std::string str;
	bool parsingMove = false;
	while (pgnFile >> str) {
		std::size_t periodPos = str.find('.');
		if (periodPos != std::string::npos)

	}
}

void PieceMovesTest::makeMoveAndCheck(const std::uint64_t startPos, const std::uint64_t endPos,
                                      const char promotionPiece, const bool capture) {
	const std::vector<std::uint64_t> setBitsBeforeMove = Board::getSetBits(board.getGlobalBB());
	bool movementSuccessful = board.makeMove(startPos, endPos, promotionPiece);

	const std::vector<std::uint64_t> setBits = Board::getSetBits(board.getGlobalBB());
	bool startPosUnset = true, endPosSet = false;
	for (std::uint64_t bitPos : setBits) {
		if (bitPos == startPos)
			startPosUnset = false;
		else if (bitPos == endPos)
			endPosSet = true;
	}

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
	// Checkmate test

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
