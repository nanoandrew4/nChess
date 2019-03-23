#include <io/MoveReader.h>
#include <iostream>
#include <numeric>

std::string MoveReader::readMove() {
	if (storedMoveReadPos != storedMoveWritePos) // Read from stored buffer is most likely scenario
		return storedMovesBuffer[storedMoveReadPos++];

	stream.read(buf, sizeof(buf));
	std::streamsize k = stream.gcount();
	if (k != BUF_SIZE)
		stream.close();
	bytesRead += k;

	for (int i = 0; i < k; ++i) {
		switch (buf[i]) {
			case '\r':
				break;
			case '\n':
				storedMovesBuffer[storedMoveWritePos++] = move;
				storedMovesBuffer[storedMoveWritePos++] = ""; // Store empty string to signify end of match
				move = "";
				break;
			case ' ':
				storedMovesBuffer[storedMoveWritePos++] = move;
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

	return storedMovesBuffer[storedMoveReadPos++];
}
