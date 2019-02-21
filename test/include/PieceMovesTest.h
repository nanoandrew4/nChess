#ifndef NCHESS_PIECEMOVESTEST_H
#define NCHESS_PIECEMOVESTEST_H


#include <Board.hpp>
#include "Test.h"

class PieceMovesTest : public Test {
private:
	void test() override;

	void makeMoveAndCheck(std::uint64_t startPos, std::uint64_t endPos, char promotionPiece, bool capture);

	Board board;
	unsigned long moveNumber = 0;

	std::string genFailedToRemoveErrorMessage() const;

	std::string genFailedToMoveErrorMessage() const;

	std::string genFailedToRemoveCapturedPieceErrorMessage() const;
};


#endif //NCHESS_PIECEMOVESTEST_H
