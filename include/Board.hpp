#pragma once

#include <vector>
#include <array>
#include <cstdint>
#include <string>
#include <iostream>

class Board {

public:
	Board();

	explicit Board(const Board *b);

	~Board() = default;

	void displayBoard() const;

	bool makeMove(std::uint64_t startPos, std::uint64_t endPos, char promotionPiece);

	unsigned long getCurrentTurn() const { return currentTurn; }

	static std::vector<std::uint64_t> getSetBits(std::uint64_t bb);

	std::uint64_t getGlobalBB() const { return globalBB; }

	bool hasWhiteWon() { return whiteWins; }

	bool isMatchOver() { return matchOver; }

	void setDebug(bool debug) { Board::debug = debug; }

	bool isDebugEnable() { return debug; }

private:
	/*
	 * All positions are little-endian. These values set the initial positions for the bit boards
	 */
	std::uint64_t globalBB = 0xffff00000000ffff; // Might not be that useful... Consider removing in favor or orig color BBs
	std::uint64_t movedBB = 0; // For tracking king/rook moves for castling and pawn moves for en passant

	std::uint64_t whiteBB = 0x000000000000ffff;
	std::uint64_t blackBB = 0xffff000000000000;

	std::uint64_t whitePawnBB = 0x000000000000ff00;
	std::uint64_t whiteKnightBB = 0x0000000000000042;
	std::uint64_t whiteBishopBB = 0x0000000000000024;
	std::uint64_t whiteRookBB = 0x0000000000000081;
	std::uint64_t whiteQueenBB = 0x0000000000000010;
	std::uint64_t whiteKingBB = 0x0000000000000008;

	std::uint64_t blackPawnBB = 0x00ff000000000000;
	std::uint64_t blackKnightBB = 0x4200000000000000;
	std::uint64_t blackBishopBB = 0x2400000000000000;
	std::uint64_t blackRookBB = 0x8100000000000000;
	std::uint64_t blackQueenBB = 0x1000000000000000;
	std::uint64_t blackKingBB = 0x0800000000000000;

	unsigned long currentTurn = 0;

	std::uint64_t *currBB = &whiteBB;

	std::vector<Board> boardHistory;

	bool matchOver = false;
	bool whiteWins = false;

	static bool debug;

	void clone(const Board *src, Board *dest);

	static void loadPiecesToVisBoard(std::vector<std::string> &board, std::uint64_t bitBoard, std::uint64_t offset,
	                                 std::string displayValue);

	bool promotePawn(char promotionPiece, std::uint64_t pos);

	bool removeCapturedPiece(std::uint64_t piecePos);

	void endTurn();

	void undoMove();

	bool isValidDiagMove(std::uint64_t startPos, std::uint64_t endPos);

	bool isValidStraightMove(std::uint64_t startPos, std::uint64_t endPos);

	bool canCastle(std::uint64_t startPos, std::uint64_t endPos);

	bool enPassant(std::uint64_t endPos);

	bool movePawnIfLegal(std::uint64_t startPos, std::uint64_t endPos);

	bool moveRookIfLegal(std::uint64_t startPos, std::uint64_t endPos);

	bool moveKnightIfLegal(std::uint64_t startPos, std::uint64_t endPos);

	bool moveBishopIfLegal(std::uint64_t startPos, std::uint64_t endPos);

	bool moveQueenIfLegal(std::uint64_t startPos, std::uint64_t endPos);

	bool moveKingIfLegal(std::uint64_t startPos, std::uint64_t endPos);

	void movePieceOnBB(std::uint64_t startPos, std::uint64_t endPos, std::uint64_t &pieceBB);
};