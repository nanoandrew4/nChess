#include "Board.hpp"

#include <bitset>
#include <pieces/King.hpp>


#include "pieces/Rook.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Bishop.hpp"

bool Board::debug = false;

Board::Board() {
	this->boardHistory.reserve(100);
}

Board::Board(const Board *b) {
	clone(b, this);
}

void Board::clone(const Board *src, Board *dest) {
	dest->globalBB = src->globalBB;

	dest->whiteBB = src->whiteBB;
	dest->whitePawnBB = src->whitePawnBB;
	dest->whiteRookBB = src->whiteRookBB;
	dest->whiteKnightBB = src->whiteKnightBB;
	dest->whiteBishopBB = src->whiteBishopBB;
	dest->whiteQueenBB = src->whiteQueenBB;
	dest->whiteKingBB = src->whiteKingBB;

	dest->blackBB = src->blackBB;
	dest->blackPawnBB = src->blackPawnBB;
	dest->blackRookBB = src->blackRookBB;
	dest->blackKnightBB = src->blackKnightBB;
	dest->blackBishopBB = src->blackBishopBB;
	dest->blackQueenBB = src->blackQueenBB;
	dest->blackKingBB = src->blackKingBB;

//	dest->currentTurn = src->currentTurn;
}

void Board::displayBoard() const {
	std::vector<std::string> board(64 * 4, "  ");

	loadPiecesToVisBoard(board, whitePawnBB, 0, "wP");
	loadPiecesToVisBoard(board, whiteRookBB, 0, "wR");
	loadPiecesToVisBoard(board, whiteKnightBB, 0, "wN");
	loadPiecesToVisBoard(board, whiteBishopBB, 0, "wB");
	loadPiecesToVisBoard(board, whiteQueenBB, 0, "wQ");
	loadPiecesToVisBoard(board, whiteKingBB, 0, "wK");

	loadPiecesToVisBoard(board, blackPawnBB, 0, "bP");
	loadPiecesToVisBoard(board, blackRookBB, 0, "bR");
	loadPiecesToVisBoard(board, blackKnightBB, 0, "bN");
	loadPiecesToVisBoard(board, blackBishopBB, 0, "bB");
	loadPiecesToVisBoard(board, blackQueenBB, 0, "bQ");
	loadPiecesToVisBoard(board, blackKingBB, 0, "bK");

	loadPiecesToVisBoard(board, globalBB, 64, "gP");
	loadPiecesToVisBoard(board, whiteBB, 128, "ww");
	loadPiecesToVisBoard(board, blackBB, 192, "bb");

	for (int i = 0; i < 8; ++i) {
		if (i != 0)
			std::cout << std::endl;
		std::cout << 8 - i << ' ';

		for (unsigned long j = 0; j < 8; ++j)
			std::cout << board.at(63 - ((i * 8) + j));
		std::cout << "    ";
		for (unsigned long j = 0; j < 8; ++j)
			std::cout << board.at(127 - ((i * 8) + j));
		std::cout << "    ";
		for (unsigned long j = 0; j < 8; ++j)
			std::cout << board.at(191 - ((i * 8) + j));
		std::cout << "    ";
		for (unsigned long j = 0; j < 8; ++j)
			std::cout << board.at(255 - ((i * 8) + j));
	}

	std::string boardLetters = "a b c d e f g h";
	std::cout << std::endl
	          << "   ";
	for (int i = 0; i < 4; ++i)
		std::cout << boardLetters << "     ";
	std::cout << std::endl
	          << std::endl;
}

void
Board::loadPiecesToVisBoard(std::vector<std::string> &board, const std::uint64_t bitBoard, const std::uint64_t offset,
                            const std::string displayValue) {
	std::vector<short> pieces = getSetBits(bitBoard);
	for (short piece : pieces)
		board.at(piece + offset) = displayValue;
}

std::vector<short> Board::getSetBits(const std::uint64_t bb) {
	std::vector<short> setBits;
	setBits.reserve(16);
	for (short i = 0; i < 64; ++i)
		if ((bb & (1ul << i)) != 0)
			setBits.push_back(i);
	return setBits;
}

bool Board::promotePawn(char promotionPiece, std::uint64_t pos) {
	(*currBB == whiteBB ? whitePawnBB : blackPawnBB) -= (1ul << pos);

	if (promotionPiece == 'Q')
		(*currBB == whiteBB ? whiteQueenBB : blackQueenBB) += (1ul << pos);
	else if (promotionPiece == 'R')
		(*currBB == whiteBB ? whiteRookBB : blackRookBB) += (1ul << pos);
	else if (promotionPiece == 'N')
		(*currBB == whiteBB ? whiteKnightBB : blackKnightBB) += (1ul << pos);
	else if (promotionPiece == 'B')
		(*currBB == whiteBB ? whiteBishopBB : blackBishopBB) += (1ul << pos);
	else
		return false;
	return true;
}

bool Board::removeCapturedPiece(std::uint64_t piecePos) {
	if (debug)
		std::cout << "Removing captured piece" << std::endl;
	std::uint64_t bitPos = (1ul << piecePos);

	if ((bitPos & (*currBB == whiteBB ? blackPawnBB : whitePawnBB)) != 0)
		(*currBB == whiteBB ? blackPawnBB : whitePawnBB) -= bitPos;
	else if ((bitPos & (*currBB == whiteBB ? blackRookBB : whiteRookBB)) != 0)
		(*currBB == whiteBB ? blackRookBB : whiteRookBB) -= bitPos;
	else if ((bitPos & (*currBB == whiteBB ? blackKnightBB : whiteKnightBB)) != 0)
		(*currBB == whiteBB ? blackKnightBB : whiteKnightBB) -= bitPos;
	else if ((bitPos & (*currBB == whiteBB ? blackBishopBB : whiteBishopBB)) != 0)
		(*currBB == whiteBB ? blackBishopBB : whiteBishopBB) -= bitPos;
	else if ((bitPos & (*currBB == whiteBB ? blackQueenBB : whiteQueenBB)) != 0)
		(*currBB == whiteBB ? blackQueenBB : whiteQueenBB) -= bitPos;
	else if ((bitPos & (*currBB == whiteBB ? blackKingBB : whiteKingBB)) != 0) {
		// Undo move that led to king being taken, and continue search
		// Maybe track occurrences to see if it is worth handling some other way
		std::cout << "King capture attempted, skipping move in tree..." << std::endl;
		undoMove();
		return false;
	} else {
		std::cout << "There is no piece to remove..." << std::endl;
		return false;
	}

	(*currBB == whiteBB ? blackBB : whiteBB) -= bitPos;
	globalBB -= bitPos;
	return true;
}

bool Board::makeMove(const std::uint64_t &startPos, const std::uint64_t &endPos, const char promotionPiece) {
	if (debug)
		std::cout << "Startpos: " << startPos << " endPos: " << endPos << std::endl;
	if (startPos > 63 || endPos > 63) {
		std::cout << "Piece is moving off the board..." << std::endl;
		return false;
	}

	if ((*currBB & (1ul << startPos)) == 0) {
		std::cout << "No piece to move" << std::endl;
		return false;
	}

	if ((*currBB & (1ul << endPos)) != 0) {
		std::cout << "Cannot capture own piece" << std::endl;
		return false;
	}

	bool legal;
	std::uint64_t startPosBit = 1ul << startPos;
	if ((whitePawnBB & startPosBit) != 0 || (blackPawnBB & startPosBit) != 0) {
		legal = movePawnIfLegal(startPos, endPos);
		if (legal && (endPos >> 3u == 7 || endPos >> 3u == 0))
			if (!promotePawn(promotionPiece, endPos)) {
				std::cout << "No promotion piece selected" << std::endl;
				undoMove();
				return false;
			}
	} else if ((whiteRookBB & startPosBit) != 0 || (blackRookBB & startPosBit) != 0)
		legal = moveRookIfLegal(startPos, endPos);
	else if ((whiteKnightBB & startPosBit) != 0 || (blackKnightBB & startPosBit) != 0)
		legal = moveKnightIfLegal(startPos, endPos);
	else if ((whiteBishopBB & startPosBit) != 0 || (blackBishopBB & startPosBit) != 0)
		legal = moveBishopIfLegal(startPos, endPos);
	else if ((whiteQueenBB & startPosBit) != 0 || (blackQueenBB & startPosBit) != 0)
		legal = moveQueenIfLegal(startPos, endPos);
	else if ((whiteKingBB & startPosBit) != 0 || (blackKingBB & startPosBit) != 0)
		legal = moveKingIfLegal(startPos, endPos);
	else {
		std::cout << "No piece was moved" << std::endl;
		return false;
	}

	if (!legal)
		return false;

	legal = true; // Reset to check legality of piece capture
	if (((*currBB == whiteBB ? blackBB : whiteBB) & (1ul << endPos)) != 0)
		legal = removeCapturedPiece(endPos);

	if (legal)
		endTurn();
	return true;
}

void Board::endTurn() {
	++currentTurn; // Turn changed before saving board, so that if move is undone the turn is given to the right player
	boardHistory.emplace_back(this); // Copies the board into a vector, so that the state can be restored if needed
	currBB = &((currentTurn & 1UL) == 0 ? whiteBB : blackBB);
}

void Board::undoMove() {
	std::cout << "Undoing move" << std::endl;
	if (!boardHistory.empty()) {
		Board prevBoardState = boardHistory.back();
		boardHistory.pop_back();
		clone(&prevBoardState, this);
	} else {
		std::cout << "Undo should not have happened, no moves to undo" << std::endl; // For debugging purposes
	}
}

void Board::movePieceOnBB(const std::uint64_t &startPos, const std::uint64_t &endPos, std::uint64_t &pieceBB) {
	const std::uint64_t movePieceOp = ((1ul << endPos) - (1ul << startPos));
	*currBB += movePieceOp;
	pieceBB += movePieceOp;
	globalBB += movePieceOp;
}

bool Board::enPassant(std::uint64_t endPos) {
	const bool isWhiteTurn = *currBB == whiteBB;
	const std::uint64_t potentialEnPassantCapturePos = isWhiteTurn ? endPos - 8u : endPos + 8u;

	const std::uint64_t captureBitPos = 1ul << potentialEnPassantCapturePos;
	if (((isWhiteTurn ? blackPawnBB : whitePawnBB) & captureBitPos) != 0 && (movedBB & captureBitPos) != 0) {
		removeCapturedPiece(potentialEnPassantCapturePos);
		return true;
	}

	return false;
}

bool Board::movePawnIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	const std::uint64_t posDiff = endPos > startPos ? endPos - startPos : startPos - endPos;
	const bool isWhiteTurn = *currBB == whiteBB;

	if (((isWhiteTurn ? Pawn::getWhiteMoves().at(startPos) : Pawn::getBlackMoves().at(startPos)) &
	     (1ul << endPos)) == 0) {
		std::cout << "Illegal pawn move" << std::endl;
		return false;
	} else if (posDiff == 8 && (globalBB & (1ul << endPos)) != 0) {
		std::cout << "Attempting to move pawn atop another piece while moving vertically" << std::endl;
		return false;
	} else if ((posDiff == 7 || posDiff == 9) && (((isWhiteTurn ? blackBB : whiteBB) & (1ul << endPos)) ==
	                                              0) && (!enPassant(endPos))) {
		std::cout << "No piece to capture with pawn" << std::endl;
		return false;
	}

	movePieceOnBB(startPos, endPos, isWhiteTurn ? whitePawnBB : blackPawnBB);

	if (posDiff == 16 && (((startPos / 8) == 1 && isWhiteTurn) || (startPos / 8 == 6 && !isWhiteTurn)))
		movedBB += (1ul << endPos);

	return true;
}

bool Board::isValidStraightMove(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	const int step = ((endPos - startPos) % 8 == 0) ? (startPos < endPos ? 8 : -8) : (startPos < endPos ? 1 : -1);
	for (std::uint64_t pos = startPos + step; pos != endPos; pos += step) {
		if ((globalBB & (1ul << pos)) != 0) {
			std::cout << "There is a piece between the starting and ending positions" << std::endl;
			return false;
		}
	}
	return true;
}

bool Board::moveRookIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	if (((Rook::getMoves().at(startPos)) & (1ul << endPos)) != 0 && isValidStraightMove(startPos, endPos)) {
		movePieceOnBB(startPos, endPos, (*currBB == whiteBB ? whiteRookBB : blackRookBB));

		bool rookStartPos = startPos == 0 || startPos == 7 || startPos == 54 || startPos == 63;
		if ((((1ul << startPos) & movedBB) == 0) && rookStartPos)
			movedBB += (1ul << startPos);
		return true;
	} else {
		std::cout << "Rook is not moving on a file: " << startPos << " -> " << endPos << std::endl;
		return false;
	}
}

bool Board::moveKnightIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	if ((Knight::getMoves().at(startPos) & (1ul << endPos)) == 0) {
		std::cout << "Illegal knight move" << std::endl;
		return false;
	}

	movePieceOnBB(startPos, endPos, (*currBB == whiteBB ? whiteKnightBB : blackKnightBB));

	return true;
}

bool Board::isValidDiagMove(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	const bool isStartXSmallerThanEndX = endPos % 8u > startPos % 8u;
	int step = ((isStartXSmallerThanEndX && endPos > startPos) || (!isStartXSmallerThanEndX && endPos < startPos)) ? 9
	                                                                                                               : 7;
	if (endPos < startPos)
		step = ~step + 1;

	for (std::uint64_t i = startPos + step; i != endPos; i += step) {
		if ((globalBB & (1ul << i)) != 0) {
			std::cout << "Illegal diagonal move, there is a piece between the starting and ending position" <<
			          std::endl;
			return false;
		}
	}
	return true;
}

bool Board::moveBishopIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	if ((Bishop::getMoves().at(startPos) & (1ul << endPos)) != 0 && isValidDiagMove(startPos, endPos)) {
		movePieceOnBB(startPos, endPos, *currBB == whiteBB ? whiteBishopBB : blackBishopBB);
		return true;
	} else {
		std::cout << "Illegal bishop move" << std::endl;
		return false;
	}
}

bool Board::moveQueenIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	const bool isDiagMove = (Bishop::getMoves().at(startPos) & (1ul << endPos)) != 0;
	const bool isStraightMove = (Rook::getMoves().at(startPos) & (1ul << endPos)) != 0;

	if ((isDiagMove && isValidDiagMove(startPos, endPos)) ||
	    (isStraightMove && isValidStraightMove(startPos, endPos))) {
		movePieceOnBB(startPos, endPos, *currBB == whiteBB ? whiteQueenBB : blackQueenBB);
		return true;
	} else
		std::cout << "Illegal queen move" << std::endl;

	return false;
}

bool Board::canCastle(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	const bool isWhiteTurn = (currentTurn & 1) == 0;
	const bool isKingSideCastle = startPos - endPos == 2;

	if (((1ul << startPos) & movedBB) != 0)
		return false;

	if (isKingSideCastle)
		return isWhiteTurn ? ((1ul & movedBB) == 0) : ((1ul << 56) & movedBB) == 0;
	else
		return isWhiteTurn ? ((1ul << 7) & movedBB) == 0 : ((1ul << 63) & movedBB) == 0;
}

bool Board::moveKingIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos) {
	const bool isWhiteTurn = (currentTurn & 1) == 0;
	const std::array<std::uint64_t, 64> moves = isWhiteTurn ? King::getWhiteMoves() : King::getBlackMoves();
	const bool isCastlingMove = (endPos - startPos == 2 || startPos - endPos == 2);

	if (((moves.at(startPos)) & (1ul << endPos)) == 0) {
		std::cout << "Illegal king move" << std::endl;
		return false;
	} else if (isCastlingMove && !canCastle(startPos, endPos)) { // TODO: BAN CASTLE IN CHECK
		std::cout << "Illegal castling move" << std::endl;
		return false;
	}

	// TODO: MOVE INTO CHECK BAN
	// TODO: CHECK NO PIECES BETWEEN KING AND ROOK
	if (isCastlingMove) {
		const bool isKingSideCastle = startPos - endPos == 2;
		std::uint64_t rookStartPos, rookEndPos;
		if (isWhiteTurn) {
			rookStartPos = isKingSideCastle ? 0 : 7;
			rookEndPos = isKingSideCastle ? 2 : 4;
		} else {
			rookStartPos = isKingSideCastle ? 56 : 63;
			rookEndPos = isKingSideCastle ? 58 : 60;
		}
		movePieceOnBB(rookStartPos, rookEndPos, isWhiteTurn ? whiteRookBB : blackRookBB);
	}

	if ((startPos == 3 || startPos == 58) && ((1ul << startPos) & movedBB) == 0)
		movedBB += (1ul << startPos);

	movePieceOnBB(startPos, endPos, (currentTurn & 1) == 0 ? whiteKingBB : blackKingBB);

	return true;
}