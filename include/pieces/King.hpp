#pragma once

#include <array>
#include <cstdint>

class King {
public:
	/**
	 * Uses #generateMoves() internally to populate 'moves'. All possible moves for a king are encoded into this
	 * classes array.
	 */
	static void initialize();

	/**
	 * Generates all possible moves for a king at every square on the board. A bitboard is generated for each
	 * square on the board, which is encoded in a 64 bit unsigned integer. A sample bitboard might look like the
	 * following (separated into 8 rows for easier visualization, imagine as 64 bits from top left to bottom right,
	 * top left being the highest value bit):
	 *
	 * 0 0 0 0 0 0 0 0 <br>
	 * 0 0 0 0 0 0 0 0 <br>
	 * 0 0 0 0 0 0 0 0 <br>
	 * 0 0 0 0 0 0 0 0 <br>
	 * 0 0 0 0 1 1 1 0 <br>
	 * 0 0 0 0 1 0 1 0 <br>
	 * 0 0 0 0 1 1 1 0 <br>
	 * 0 0 0 0 0 0 0 0 <br>
	 *
	 * The above bitboard would be for a king at position 18 (f3) (positions are counted from bottom right to top
	 * left, so a1 is position 8, h1 is position 0, and so on). The bitboard also includes castling moves, where
	 * appropriate.
	 *
	 * @return Array of bitboards containing all the possible moves at each square on the board for a king.
	 */
	static std::array<std::uint64_t, 64> generateMoves(bool white, bool includeCastleMoves);

	/**
	 * Returns the array of bitboards representing all the possible moves for a white king. initialize() must be called
	 * before attempting to retrieve the array.
	 *
	 * @return Array of bitboards representing all the possible moves for a white king
	 */
	static std::array<std::uint64_t, 64> *getWhiteMoves() { return &whiteKingMoves; }

	/**
	 * Returns the array of bitboards representing all the possible moves for a black king. initialize() must be called
	 * before attempting to retrieve the array.
	 *
	 * @return Array of bitboards representing all the possible moves for a black king
	 */
	static std::array<std::uint64_t, 64> *getBlackMoves() { return &blackKingMoves; }

	static std::array<std::uint64_t, 64> *getNonCastleKingMoves() { return &nonCastleKingMoves; }

private:
	King() = default;

	~King() = default;

	static std::array<std::uint64_t, 64> whiteKingMoves;
	static std::array<std::uint64_t, 64> blackKingMoves;
	static std::array<std::uint64_t, 64> nonCastleKingMoves;
};