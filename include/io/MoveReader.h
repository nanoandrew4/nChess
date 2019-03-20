#ifndef NCHESS_MOVEREADER_H
#define NCHESS_MOVEREADER_H

#include <string>
#include <fstream>
#include <array>

class MoveReader {
public:
	static std::string parse(std::ifstream &stream);

private:
	static char buf[4096];
	static std::string move;

	static std::array<std::string, 65536> storedMoves;
	static std::uint16_t storedMoveReadPos;
	static std::uint16_t storedMoveWritePos;
};

#endif //NCHESS_MOVEREADER_H
