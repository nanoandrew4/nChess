#include "../include/PieceMovesTest.h"

void PieceMovesTest::test() {
	makeMoveAndCheck(15, 31, ' ', false); // White move pawn
	makeMoveAndCheck(55, 39, ' ', false); // Black move pawn
}

void PieceMovesTest::makeMoveAndCheck(const std::uint64_t startPos, const std::uint64_t endPos,
                                      const char promotionPiece, const bool capture) {
	const std::vector<std::uint64_t> setBitsBeforeMove = Board::getSetBits(board.getGlobalBB());
	board.makeMove(startPos, endPos, promotionPiece);

	const std::vector<std::uint64_t> setBits = Board::getSetBits(board.getGlobalBB());
	bool startPosUnset = true, endPosSet = false;
	for (std::uint64_t bitPos : setBits) {
		if (bitPos == startPos)
			startPosUnset = false;
		else if (bitPos == endPos)
			endPosSet = true;
	}

	if (!startPosUnset)
		logTestFailure(TestFailData("PieceMovesTest", genFailedToRemoveErrorMessage()));
	if (!endPosSet)
		logTestFailure(TestFailData("PieceMovesTest", genFailedToMoveErrorMessage()));
	if (capture && setBitsBeforeMove.size() != setBits.size() + 1)
		logTestFailure(TestFailData("PieceMovesTest", genFailedToRemoveCapturedPieceErrorMessage()));

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
