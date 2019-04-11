#ifndef NCHESS_PIECEMOVESTEST_H
#define NCHESS_PIECEMOVESTEST_H

#include <string>
#include <Board.hpp>
#include "Test.h"

class PieceMovesTest : public Test {
public:
	explicit PieceMovesTest() = default;

	void setPathToTestFile(const std::string &path) { pathToTestFile = path; }

	void setStartMatch(const unsigned long startMatch) { this->startMatch = startMatch; }

	void setStartMove(const unsigned long startMove) { this->startMove = startMove; }

private:
	unsigned long moveNumber = 0;
	unsigned long matchNumber = 0;

	unsigned long startMove = 0;
	unsigned long startMatch = 0;

	std::string pathToTestFile;

	void test() override;

	bool makeMoveAndCheck(const std::array<char, 5> &move, Board &board);

	std::string genFailedToRemoveErrorMessage() const;

	std::string genFailedToMoveErrorMessage() const;

	std::string genFailedToRemoveCapturedPieceErrorMessage() const;

	std::string genFailedToMakeMoveErrorMessage() const;
};


#endif //NCHESS_PIECEMOVESTEST_H
