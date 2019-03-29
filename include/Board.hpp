#pragma once

#include <vector>
#include <array>
#include <cstdint>
#include <string>
#include <iostream>

class Board {

public:
	Board();

	~Board() = default;

	/**
	 * Copy ctor. Copies all fields to a new instance of this class, except for the move history and currentTurn.
	 * @param b Board to copy to
	 */
	explicit Board(const Board *b);

	/**
	 * Prints a visual representation of the board to the screen. Four boards are drawn, one which is the actual game
	 * board, one containing the white pieces, one containing the black pieces, and a representation of the global
	 * bitboard.
	 */
	void displayBoard() const;

	/**
	 * Attempts to make a move for the current player on the board. If the move is illegal, an error will be displayed.
	 *
	 * @param startPos The current position of the piece to move. Must be a value between 0 and 63 (both inclusive),
	 * where 0 is the bottom right corner of the board, and 63 is the top left corner
	 * @param endPos The target destination for the piece. Must be a value between 0 and 63 (both inclusive),
	 * where 0 is the bottom right corner of the board, and 63 is the top left corner
	 * @param promotionPiece Only applicable when a pawn promotion occurs, and must be one of the following values: 'Q',
	 * 'R','N','R'.
	 * @return True if the move the move was performed, false if it was not due to it being illegal
	 */
	bool makeMove(const std::uint64_t &startPos, const std::uint64_t &endPos, char promotionPiece);

	/**
	 * Returns the current turn on the board, with 0 being the first turn
	 *
	 * @return Current turn on the board
	 */
	unsigned long getCurrentTurn() const { return currentTurn; }

	/**
	 * Returns a vector containing the bit positions that are set for the given bitboard.
	 *
	 * @param bb Bitboard which to extract the set bits for
	 * @return Vector containing the positions of the set bits in the supplied bitboard
	 */
	static std::vector<short> getSetBits(std::uint64_t bb);

	/**
	 * Returns the global bitboard
	 *
	 * @return The global bitboard
	 */
	std::uint64_t getGlobalBB() const { return (whiteBB | blackBB); }

	/**
	 * Returns true if white has won the match, or false otherwise
	 *
	 * @return Whether white has won the match
	 */
	bool hasWhiteWon() { return whiteWins; }

	/**
	 * Returns true if the match has ended, or false otherwise.
	 *
	 * @return Whether the match has ended
	 */
	bool isMatchOver() { return matchOver; }

private:

	/*
	 * All positions are little-endian. These values set the initial positions for the bit boards.
	 */
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

	std::uint64_t *currBB = &whiteBB;

	unsigned short currentTurn = 0;

	bool matchOver = false;
	bool whiteWins = false;

#ifdef PRINT_DEBUG_MESSAGES
	static constexpr bool debug = true;
#else
	static constexpr bool debug = false;
#endif

	void clone(const Board *src, Board *dest);

	static void loadPiecesToVisBoard(std::vector<std::string> &board, std::uint64_t bitBoard, std::uint64_t offset,
	                                 const std::string &displayValue);

	bool promotePawn(char promotionPiece, std::uint64_t pos);

	bool removeCapturedPiece(const std::uint64_t &piecePos);

	void endTurn();

	bool isValidDiagMove(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool isValidStraightMove(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool canCastle(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool enPassant(std::uint64_t endPos);

	bool movePawnIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool moveRookIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool moveKnightIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool moveBishopIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool moveQueenIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool moveKingIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	void movePieceOnBB(const std::uint64_t &startPos, const std::uint64_t &endPos, std::uint64_t &pieceBB);
};