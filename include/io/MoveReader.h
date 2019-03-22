#ifndef NCHESS_MOVEREADER_H
#define NCHESS_MOVEREADER_H

#include <string>
#include <fstream>
#include <array>

class MoveReader {
public:
	explicit MoveReader(std::ifstream &stream) { this->stream = std::move(stream); }

	std::string readMove();

	unsigned long getBytesRead() const { return bytesRead; }

	bool finishedReading() const { return storedMoveReadPos == storedMoveWritePos && !stream.is_open(); }

private:
	std::ifstream stream;

	static const int BUF_SIZE = 4096;
	char buf[BUF_SIZE] = {};
	std::string move;

	std::array<std::string, 65536> storedMoves{""};
	std::uint16_t storedMoveReadPos = 0;
	std::uint16_t storedMoveWritePos = 0;

	unsigned long bytesRead = 0;
};

#endif //NCHESS_MOVEREADER_H
