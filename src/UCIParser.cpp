#include <chrono>
#include <UCIParser.hpp>

double UCIParser::microSecondInBoard = 0;

bool UCIParser::parse(Board &board, std::string moveStr) {
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

	return moveOnBoard(board, startPos, endPos, promotionPiece);
}

bool UCIParser::parseAndTime(Board &board, std::string moveStr) {
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

	auto start = std::chrono::high_resolution_clock::now();

	const bool moveSuccessful = moveOnBoard(board, startPos, endPos, promotionPiece);

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	microSecondInBoard = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

	return moveSuccessful;
}

bool UCIParser::isPromotionPiece(const char piece) {
	return piece == 'Q' || piece == 'R' || piece == 'B' || piece == 'N';
}

bool UCIParser::notColumn(char val) {
	return val < 97 || val > 104;
}

bool UCIParser::notRow(char val) {
	return val < 49 || val > 56;
}

bool UCIParser::moveOnBoard(Board &board, const std::uint64_t startPos, const std::uint64_t endPos,
                            const char promotionPiece) {
	return board.makeMove(startPos, endPos, promotionPiece);
}
