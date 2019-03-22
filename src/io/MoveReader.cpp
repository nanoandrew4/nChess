#include <io/MoveReader.h>
#include <iostream>
#include <numeric>

#define likely(x)     __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

std::string MoveReader::readMove() {
	if (likely(storedMoveReadPos != storedMoveWritePos))
		return storedMoves[storedMoveReadPos++];

	stream.read(buf, sizeof(buf));
	std::streamsize k = stream.gcount();
	if (unlikely(k != BUF_SIZE))
		stream.close();
	bytesRead += k;
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
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case 'Q':
			case 'R':
			case 'B':
			case 'N':
				move.append(1, buf[i]);
				break;
			default:
				break;
		}
	}

	return storedMoves[storedMoveReadPos++];
}
