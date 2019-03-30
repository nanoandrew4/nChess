#pragma once

#include <array>
#include <cstdlib>

class Rook {
public:
	/**
	 * Uses #generateMoves() internally to populate 'rookMoves'. All possible moves for a rook are encoded into the
	 * array.
	 */
	static void initialize();

	/**
	   * Generates all possible moves for a rook at every square on the board. A bitboard is generated for each
	   * square on the board, which is encoded in a 64 bit unsigned integer. A sample bitboard might look like the
	   * following (separated into 8 rows for easier visualization, imagine as 64 bits from top left to bottom right,
	   * top left being the highest value bit):
	   *
	   * 0 0 0 0 0 1 0 0 <br>
	   * 0 0 0 0 0 1 0 0 <br>
	   * 0 0 0 0 0 1 0 0 <br>
	   * 0 0 0 0 0 1 0 0 <br>
	   * 0 0 0 0 0 1 0 0 <br>
	   * 0 0 0 0 0 1 0 0 <br>
	   * 0 0 0 0 0 1 0 0 <br>
	   * 1 1 1 1 1 0 1 1 <br>
	   *
	   * The above bitboard would be for a rook at position 3 (f1) (positions are counted from bottom right to top
	   * left, so a1 is position 8, h1 is position 0, and so on)
	   *
	   * @return Array of bitboards containing all the possible moves at each square on the board for a rook.
	   */
	static std::array<std::uint64_t, 64> generateMoves();

	/**
	   * Returns the array of bitboards representing all the possible moves for a rook. initialize() must be called 
	   * before attempting to retrieve the array.
	   *
	   * @return Array of bitboards representing all the possible moves for a rook
	   */
	const static std::array<std::uint64_t, 64> *getMoves() { return &rookMoves; }

private:
	Rook() = default;

	~Rook() = default;

	static std::array<std::uint64_t, 64> rookMoves;
};