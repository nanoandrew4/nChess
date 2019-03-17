#ifndef NCHESS_PIECEMOVESTEST_H
#define NCHESS_PIECEMOVESTEST_H

#include <string>
#include <Board.hpp>
#include "Test.h"

class PieceMovesTest : public Test {
public:
	explicit PieceMovesTest();

private:
	unsigned long moveNumber = 0;
	unsigned long matchNumber = 0;

	std::string pathToTestFile;

	void test() override;

	void makeMoveAndCheck(const std::string &move, Board &board);

	std::string genFailedToRemoveErrorMessage() const;

	std::string genFailedToMoveErrorMessage() const;

	std::string genFailedToRemoveCapturedPieceErrorMessage() const;

	std::string genFailedToMakeMoveErrorMessage() const;
};


#endif //NCHESS_PIECEMOVESTEST_H
