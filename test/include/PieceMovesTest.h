#ifndef NCHESS_PIECEMOVESTEST_H
#define NCHESS_PIECEMOVESTEST_H

#include <string>
#include <Board.hpp>
#include "Test.h"

class PieceMovesTest : public Test {
public:
	static void setTestFile(const std::string &pathToFile) { PieceMovesTest::pathToTestFile = pathToFile; };

private:
	Board board;
	unsigned long moveNumber = 0;
	static std::string pathToTestFile;

	void test() override;

	void makeMoveAndCheck(std::uint64_t startPos, std::uint64_t endPos, char promotionPiece, bool capture);

	std::string genFailedToRemoveErrorMessage() const;

	std::string genFailedToMoveErrorMessage() const;

	std::string genFailedToRemoveCapturedPieceErrorMessage() const;

	std::string genFailedToPromoteErrorMessage() const;

	std::string genFailedToMakeMoveErrorMessage() const;
};


#endif //NCHESS_PIECEMOVESTEST_H
