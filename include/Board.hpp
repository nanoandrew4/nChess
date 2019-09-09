#pragma once

#include <vector>
#include <array>
#include <cstdint>
#include <string>
#include <iostream>

class Board {

public:
	Board() = default;

	~Board() = default;

	/**
	 * Copy ctor. Copies all fields to a new instance of this class, except for the move history and currentTurn.
	 * @param b Board to copy to
	 */
	explicit Board(Board *b);

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
	 * Returns the current turn on the board, with 0 being the first turn.
	 *
	 * @return Current turn on the board
	 */
	[[nodiscard]] unsigned short getCurrentTurn() const { return currentTurn; }

	/**
	 * Returns a vector containing the bit positions that are set for the given bitboard.
	 *
	 * @param bb Bitboard which to extract the set bits for
	 * @return Vector containing the positions of the set bits in the supplied bitboard
	 */
	static std::vector<std::uint8_t> getSetBits(const std::uint64_t &bb);

	/**
	 * Returns the global bitboard
	 *
	 * @return The global bitboard
	 */
	[[nodiscard]] std::uint64_t getGlobalBB() const { return (whiteBB | blackBB); }

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
	 * All positions are little-endian. These values set the initial positions for the bit boards, where each set bit
	 * represents a piece of the bitboard type existing at that bit position.
	 */
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

	std::uint64_t movedBB = 0; // For tracking king/rook moves for castling and pawn moves for en passant

	std::uint64_t *currBB = &whiteBB;

	unsigned short currentTurn = 0;

	bool matchOver = false;
	bool whiteWins = false;

	std::vector<Board> boardHistory;

#ifdef PRINT_DEBUG_MESSAGES
	static constexpr bool debug = true;
#else
	static constexpr bool debug = false;
#endif

	/**
	 * Clones a Board instance into the specified target
	 *
	 * @param src Board to copy data from
	 * @param dest Board to copy data to
	 */
	void clone(const Board *src, Board *dest);

	// Debugging method
	static void loadPiecesToVisBoard(std::vector<std::string> &board, const std::uint64_t &bitBoard,
	                                 const std::uint64_t &offset, const std::string &displayValue);

	/**
	 * Promotes the piece at the given position with the given piece type. No verification that the piece
	 * to be promoted is a pawn or that the piece is on the last rank is done by this function.
	 *
	 * @param promotionPiece The piece to promote to, can be one of: 'Q', 'R', 'B', 'N'
	 * @param pos Bitboard position at which the piece to be promoted is at
	 * @return True if the piece was promoted, false if the supplied promotionPiece did not match one of the valid
	 * values
	 */
	bool promotePawn(char promotionPiece, std::uint64_t pos);

	/**
	 * Removes the piece at the given position from the board.
	 *
	 * @param piecePos Bitboard position of the piece to remove
	 * @return True if the piece was successfully removed, false otherwise
	 */
	bool removeCapturedPiece(const std::uint64_t &piecePos);

	void undoMove();

	void endTurn();

	/**
	 * Determines whether a diagonal move is valid, that is, if it would collide with any pieces as it slides.
	 * Does not check whether there is a piece at the end position, or that it is not of the own players color. Those
	 * checks are handled in the makeMove() function.
	 *
	 * @param startPos Position from which the piece would start moving
	 * @param endPos Position at which the piece would stop moving
	 * @return True if the diagonal move does not collide with other pieces as it slides, false otherwise
	 */
	bool isValidDiagMove(const std::uint64_t &startPos, const std::uint64_t &endPos);

	/**
	 * Determines whether a horizontal/vertical move is valid, that is, if it would collide with any pieces as it
	 * slides. Does not check whether there is a piece at the end position, or that it is not of the own players color.
	 * Those checks are handled in the makeMove() function.
	 *
	 * @param startPos Position from which the piece would start moving.
	 * @param endPos Position at which the piece would stop moving
	 * @return True if the horizontal/vertical does not collide with any pieces as it slides, false otherwise
	 */
	bool isValidStraightMove(const std::uint64_t &startPos, const std::uint64_t &endPos);

	/**
	 * Determines whether a castling move is legal or not, based on whether the king or rooks have moved from their
	 * initial position.
	 *
	 * @param startPos Starting position for the castling move
	 * @param endPos Ending position for the castling move
	 * @return True if the castling move is legal, false otherwise
	 */
	bool canCastle(const std::uint64_t &startPos, const std::uint64_t &endPos);

	/**
	 * Determines the legality of an en passant move, based on the positioning of the pawns.
	 */
	bool enPassant(const std::uint64_t &endPos);

	bool isPawnMoveLegal(const std::uint64_t &startPos, const std::uint64_t &endPos, bool isWhiteTurn);

	/**
	 * Attempts to move a pawn from the specified position to the target position. If the move is not determined to be
	 * illegal, it will be performed, but captured pieces are not removed inside this function, that is left for
	 * makeMove() to handle.
	 *
	 * @param startPos Position where the selected pawn is at
	 * @param endPos Position where the pawn should be moved to
	 * @return True if the move was legal and the pawn was moved, false if the move was illegal
	 */
	bool movePawnIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool isRookMoveLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	/**
	 * Attempts to move a rook from the specified position to the target position. If the move is not determined to be
	 * illegal, it will be performed, but captured pieces are not removed inside this function, that is left for
	 * makeMove() to handle.
	 *
	 * @param startPos Position where the selected rook is at
	 * @param endPos Position where the rook should be moved to
	 * @return True if the move was legal and the rook was moved, false if the move was illegal
	 */
	bool moveRookIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool isKnightMoveLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	/**
	 * Attempts to move a knight from the specified position to the target position. If the move is not determined to be
	 * illegal, it will be performed, but captured pieces are not removed inside this function, that is left for
	 * makeMove() to handle.
	 *
	 * @param startPos Position where the selected knight is at
	 * @param endPos Position where the knight should be moved to
	 * @return True if the move was legal and the knight was moved, false if the move was illegal
	 */
	bool moveKnightIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool isBishopMoveLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	/**
	 * Attempts to move a bishop from the specified position to the target position. If the move is not determined to be
	 * illegal, it will be performed, but captured pieces are not removed inside this function, that is left for
	 * makeMove() to handle.
	 *
	 * @param startPos Position where the selected bishop is at
	 * @param endPos Position where the bishop should be moved to
	 * @return True if the move was legal and the bishop was moved, false if the move was illegal
	 */
	bool moveBishopIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool isQueenMoveLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	/**
	 * Attempts to move a queen from the specified position to the target position. If the move is not determined to be
	 * illegal, it will be performed, but captured pieces are not removed inside this function, that is left for
	 * makeMove() to handle.
	 *
	 * @param startPos Position where the selected queen is at
	 * @param endPos Position where the queen should be moved to
	 * @return True if the move was legal and the queen was moved, false if the move was illegal
	 */
	bool moveQueenIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool isKingMoveLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	/**
	 * Attempts to move a king from the specified position to the target position. If the move is not determined to be
	 * illegal, it will be performed, but captured pieces are not removed inside this function, that is left for
	 * makeMove() to handle.
	 *
	 * @param startPos Position where the selected king is at
	 * @param endPos Position where the king should be moved to
	 * @return True if the move was legal and the king was moved, false if the move was illegal
	 */
	bool moveKingIfLegal(const std::uint64_t &startPos, const std::uint64_t &endPos);

	bool isSquareUnderAttack(const std::uint64_t &pos, bool isWhiteTurn);

	/**
	 * Moves a piece on the specified bitboard, as well as the current players bitboard, from the specified starting
	 * position, to the specified ending position.
	 *
	 * @param startPos Position where the piece to move is at
	 * @param endPos Position where the piece to move is at
	 * @param pieceBB Bitboard corresponding to the piece that is to be moved
	 */
	void movePieceOnBB(const std::uint64_t &startPos, const std::uint64_t &endPos, std::uint64_t &pieceBB);
};