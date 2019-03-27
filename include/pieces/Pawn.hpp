#pragma once

#include <array>
#include <cstdint>

class Pawn {
public:
	/**
	 * Uses #generateMoves() internally to populate 'whitePawnMoves' and 'blackPawnMoves'. All possible moves for each
	 * color pawn are encoded into their respective array.
	 */
	static void initialize();

	/**
	   * Generates all possible moves for a pawn at every square on the board. A bitboard is generated for each
	   * square on the board, which is encoded in a 64 bit unsigned integer. A sample bitboard might look like the
	   * following (separated into 8 rows for easier visualization, imagine as 64 bits from top left to bottom right,
	   * top left being the highest value bit):
	   *
	   * 0 0 0 0 0 0 0 0 <br>
	   * 0 0 0 0 0 0 0 0 <br>
	   * 0 0 0 0 0 0 0 0 <br>
	   * 0 0 0 0 0 0 0 0 <br>
	   * 0 0 0 0 1 1 1 0 <br>
	   * 0 0 0 0 0 0 0 0 <br>
	   * 0 0 0 0 0 0 0 0 <br>
	   * 0 0 0 0 0 0 0 0 <br>
	   *
	   * The above bitboard would be for a white pawn at position 18 (f3) (positions are counted from bottom right to
	   * top left, so a1 is position 8, h1 is position 0, and so on). The above bitboard contemplates the ability for
	   * the pawn to capture, further calculations must be performed to ensure the legality of the move.
	   *
	   * @param white Determines whether to generate a bitboard for white or black pawns
	   *
	   * @return Array of bitboards containing all the possible moves at each square on the board for a pawn, white
	   * or black depending on the value of the supplied boolean.
	   */
	static std::array<std::uint64_t, 64> generateMoves(bool white);

	/**
	 * Returns the array of bitboards representing all the possible moves for a white pawn. initialize() must be called
	 * before attempting to retrieve the array.
	 *
	 * @return Array of bitboards representing all the possible moves for a white pawn
	 */
	static std::array<std::uint64_t, 64> getWhiteMoves() { return whitePawnMoves; }

	/**
	 * Returns the array of bitboards representing all the possible moves for a black pawn. initialize() must be called
	 * before attempting to retrieve the array. 
	 *
	 * @return Array of bitboards representing all the possible moves for a black pawn
	 */
	static std::array<std::uint64_t, 64> getBlackMoves() { return blackPawnMoves; }

private:
	Pawn() = default;

	~Pawn() = default;

	static std::array<std::uint64_t, 64> blackPawnMoves;
	static std::array<std::uint64_t, 64> whitePawnMoves;
};