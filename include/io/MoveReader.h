#ifndef NCHESS_MOVEREADER_H
#define NCHESS_MOVEREADER_H

#include <string>
#include <fstream>
#include <array>

class MoveReader {
public:
	explicit MoveReader(std::ifstream &stream) { this->stream = std::move(stream); }

	std::string readMove();

private:
	std::ifstream stream;

	char buf[4096] = {};
	std::string move;

	std::array<std::string, 65536> storedMoves;
	std::uint16_t storedMoveReadPos = 0;
	std::uint16_t storedMoveWritePos = 0;
};

#endif //NCHESS_MOVEREADER_H
