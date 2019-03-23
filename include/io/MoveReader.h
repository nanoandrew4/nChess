#ifndef NCHESS_MOVEREADER_H
#define NCHESS_MOVEREADER_H

#include <string>
#include <fstream>
#include <array>

class MoveReader {
public:
	explicit MoveReader(std::ifstream &stream) { this->stream = std::move(stream); }

	/**
	 * Reads a move, either from the stored moves buffer, or if all have been read, from the stream. Moves are read in
	 * bulk and stored internally to minimize I/O stalling the program.
	 *
	 * @return The next move in the stream
	 */
	std::string readMove();

	/**
	 * Returns the number of bytes read from the stream so far.
	 *
	 * @return Number of bytes read from the stream
	 */
	unsigned long getBytesRead() const { return bytesRead; }

	/**
	 * Returns true if all elements have been read out of the array, and the stream has been closed.
	 * More reliable than relying on stream.eof().
	 *
	 * @return True if the stream has been fully read
	 */
	bool finishedReading() const { return storedMoveReadPos == storedMoveWritePos && !stream.is_open(); }

private:
	std::ifstream stream;

	static const int BUF_SIZE = 4096;
	char buf[BUF_SIZE] = {};
	std::string move;

	/*
	 * Array size is 2^16 in order to allow the read and write heads to loop around the array using integer overflow,
	 * given that they are uint16_t types. This means a vector is not necessary, and gives a good speed boost.
	 */
	std::array<std::string, 65536> storedMovesBuffer{""};
	std::uint16_t storedMoveReadPos = 0;
	std::uint16_t storedMoveWritePos = 0;

	unsigned long bytesRead = 0;
};

#endif //NCHESS_MOVEREADER_H
