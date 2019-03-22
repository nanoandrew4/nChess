#include <io/MoveReader.h>
#include <iostream>
#include <numeric>

#define likely(x)     __builtin_expect((x),1)

std::string MoveReader::readMove() {
	if (likely(storedMoveReadPos != storedMoveWritePos))
		return storedMoves[storedMoveReadPos++];

	stream.read(buf, sizeof(buf));
	std::streamsize k = stream.gcount();
	for (int i = 0; i < k; ++i) {
		switch (buf[i]) {
			case '\r':
				break;
			case '\n':
				storedMoves[storedMoveWritePos++] = move;
				storedMoves[storedMoveWritePos++] = ""; // Store empty string to signify end of match
				move = "";
				break;
			case ' ':
				storedMoves[storedMoveWritePos++] = move;
				move = "";
				break;
			default:
				move.append(1, buf[i]);
				break;
		}
	}

	return storedMoves[storedMoveReadPos++];
}
