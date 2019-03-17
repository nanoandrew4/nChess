#pragma once

#include "Board.hpp"

#include <iostream>
#include <string>
#include <cstdint>

class UCIParser {
public:
	~UCIParser() = default;

	static bool parse(Board &board, std::string moveStr);

	static bool parseAndTime(Board &board, std::string moveStr);

	static bool isPromotionPiece(char piece);

	static double getSecsInBoardClass() { return microSecondInBoard / 1000000.0; }

private:
	static bool notRow(char val);

	static bool notColumn(char val);

	static bool moveOnBoard(Board &board, std::uint64_t startPos, std::uint64_t endPos,
	                        char promotionPiece);

	static double microSecondInBoard;
};