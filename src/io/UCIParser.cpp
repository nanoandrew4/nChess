#include <chrono>
#include <io/UCIParser.hpp>

bool UCIParser::parseAndMove(Board &board, std::array<char, 5> move) {
	if (move[0] == '\0' || move[1] == '\0' || move[2] == '\0' || move[3] == '\0') {
		std::cout << "Move length is invalid" << std::endl;
		return false;
	} else if (move[4] != '\0' && !isPromotionPiece(move[4])) {
		std::cout << "Promotion piece is invalid" << std::endl;
		return false;
	} else if (notColumn(move[0]) || notColumn(move[2]) || notRow(move[1]) || notRow(move[3])) {
		std::cout << "Entered move is invalid" << std::endl;
		return false;
	}

	const std::uint64_t startPos = (7u - (move[0] - 97)) + (8 * (move[1] - 49));
	const std::uint64_t endPos = (7u - (move[2] - 97)) + (8 * (move[3] - 49));
	char promotionPiece = ' ';
	if (move[4] != '\0') {
		promotionPiece = move[4];
		if (promotionPiece >= 97)
			promotionPiece -= 32; // Make uppercase
	}

	return moveOnBoard(board, startPos, endPos, promotionPiece);
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
