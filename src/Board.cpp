#include "Board.hpp"

#include <bitset>

Board::Board(const Board *b)
{
    clone(b, this);
}

void Board::clone(const Board *src, Board *dest)
{
    dest->globalBB = src->globalBB;

    dest->whiteBB = src->whiteBB;
    dest->whitePawnBB = src->whitePawnBB;
    dest->whiteRookBB = src->whiteRookBB;
    dest->whiteKnightBB = src->whiteKnightBB;
    dest->whiteBishopBB = src->whiteBishopBB;
    dest->whiteQueenBB = src->whiteQueenBB;
    dest->whiteKingBB = src->whiteKingBB;

    dest->blackBB = src->blackBB;
    dest->blackPawnBB = src->blackPawnBB;
    dest->blackRookBB = src->blackRookBB;
    dest->blackKnightBB = src->blackKnightBB;
    dest->blackBishopBB = src->blackBishopBB;
    dest->blackQueenBB = src->blackQueenBB;
    dest->blackKingBB = src->blackKingBB;

    dest->currentTurn = src->currentTurn;
    dest->boardHistory = src->boardHistory; // TODO: Check if it copies ref
}

void Board::visDebug(std::uint64_t board)
{
    std::string str = std::bitset<64>(board).to_string();

    for (int j = 0; j < 64; ++j)
    {
        if (j > 0 && j % 8 == 0)
            std::cout << std::endl;
        std::cout << str[j];
    }
    std::cout << std::endl
              << std::endl;
}

void Board::displayBoard()
{
    std::vector<std::string> board(64, "  ");

    loadPiecesToVisBoard(board, whitePawnBB, "wP");
    loadPiecesToVisBoard(board, whiteRookBB, "wR");
    loadPiecesToVisBoard(board, whiteKnightBB, "wN");
    loadPiecesToVisBoard(board, whiteBishopBB, "wB");
    loadPiecesToVisBoard(board, whiteQueenBB, "wQ");
    loadPiecesToVisBoard(board, whiteKingBB, "wK");

    loadPiecesToVisBoard(board, blackPawnBB, "bP");
    loadPiecesToVisBoard(board, blackRookBB, "bR");
    loadPiecesToVisBoard(board, blackKnightBB, "bN");
    loadPiecesToVisBoard(board, blackBishopBB, "bB");
    loadPiecesToVisBoard(board, blackQueenBB, "bQ");
    loadPiecesToVisBoard(board, blackKingBB, "bK");

    for (int i = 0; i < 64; ++i)
    {
        if (i % 8 == 0)
        {
            if (i != 0)
                std::cout << std::endl;
            std::cout << (i / 8) + 1 << ' ';
        }
        std::cout << board.at(63 - i);
    }

    std::cout << std::endl
              << "   a b c d e f g h" << std::endl
              << std::endl;
}

void Board::loadPiecesToVisBoard(std::vector<std::string> &board, const std::uint64_t bitBoard, const std::string displayValue)
{
    std::vector<std::uint64_t> pieces = getSetBits(bitBoard);
    for (std::uint64_t piece : pieces)
        board.at(piece) = displayValue;
}

std::vector<std::uint64_t> Board::getSetBits(std::uint64_t val)
{
    std::vector<std::uint64_t> setBits;
    for (std::uint64_t i = 0; i < 64; ++i)
        if ((val & (baseBit << i)) != 0)
            setBits.push_back(i);
    return setBits;
}

void Board::promotePawn(char promotionPiece, std::uint64_t pos)
{
    (*currBB == whiteBB ? whitePawnBB : blackPawnBB) -= (baseBit << pos);

    if (promotionPiece == 'Q')
        (*currBB == whiteBB ? whiteQueenBB : blackQueenBB) += (baseBit << pos);
    else if (promotionPiece == 'R')
        (*currBB == whiteBB ? whiteRookBB : blackRookBB) += (baseBit << pos);
    else if (promotionPiece == 'N')
        (*currBB == whiteBB ? whiteKnightBB : blackKnightBB) += (baseBit << pos);
    else if (promotionPiece == 'B')
        (*currBB == whiteBB ? whiteBishopBB : blackBishopBB) += (baseBit << pos);
}

bool Board::removeCapturedPiece(std::uint64_t piecePos)
{
    std::cout << "Removing captured piece" << std::endl;
    std::uint64_t bitPos = (baseBit << piecePos);

    if ((bitPos & (*currBB == whiteBB ? blackPawnBB : whitePawnBB)) != 0)
        (*currBB == whiteBB ? blackPawnBB : whitePawnBB) -= bitPos;
    else if ((bitPos & (*currBB == whiteBB ? blackRookBB : whiteRookBB)) != 0)
        (*currBB == whiteBB ? blackRookBB : whiteRookBB) -= bitPos;
    else if ((bitPos & (*currBB == whiteBB ? blackKnightBB : whiteKnightBB)) != 0)
        (*currBB == whiteBB ? blackKnightBB : whiteKnightBB) -= bitPos;
    else if ((bitPos & (*currBB == whiteBB ? blackBishopBB : whiteBishopBB)) != 0)
        (*currBB == whiteBB ? blackBishopBB : whiteBishopBB) -= bitPos;
    else if ((bitPos & (*currBB == whiteBB ? blackQueenBB : whiteQueenBB)) != 0)
        (*currBB == whiteBB ? blackQueenBB : whiteQueenBB) -= bitPos;
    else if ((bitPos & (*currBB == whiteBB ? blackKingBB : whiteKingBB)) != 0)
    {
        // Undo move that led to king being taken, and continue search
        // Maybe track occurrences to see if it is worth handling some other way
        std::cout << "King capture attempted, skipping move in tree..." << std::endl;
        undoMove();
        return false;
    }
    else
    {
        std::cout << "There is no piece to remove..." << std::endl;
        return false;
    }

    (*currBB == whiteBB ? blackBB : whiteBB) -= bitPos;
    globalBB -= bitPos;
    return true;
}

bool Board::makeMove(const std::uint64_t startPos, const std::uint64_t endPos, const char promotionPiece)
{
    std::cout << "Startpos: " << startPos << " endPos: " << endPos << std::endl;
    if (startPos > 63 || endPos > 63)
    {
        std::cout << "Piece is moving off the board..." << std::endl;
        return false;
    }

    if ((*currBB & (baseBit << startPos)) == 0)
    {
        std::cout << "No piece to move" << std::endl;
        return false;
    }

    if ((*currBB & (baseBit << endPos)) != 0)
    {
        std::cout << "Cannot capture own piece" << std::endl;
        return false;
    }

    bool legal;
    std::uint64_t startPosBit = baseBit << startPos;
    if ((whitePawnBB & startPosBit) != 0 || (blackPawnBB & startPosBit) != 0)
    {
        legal = movePawnIfLegal(startPos, endPos);
        if (legal && (endPos >> 3 == 7 || endPos >> 3 == 0))
            promotePawn(promotionPiece, endPos);
    }
    else if ((whiteRookBB & startPosBit) != 0 || (blackRookBB & startPosBit) != 0)
        legal = moveRookIfLegal(startPos, endPos);
    else if ((whiteKnightBB & startPosBit) != 0 || (blackKnightBB & startPosBit) != 0)
        legal = moveKnightIfLegal(startPos, endPos);
    else if ((whiteBishopBB & startPosBit) != 0 || (blackBishopBB & startPosBit) != 0)
        legal = moveBishopIfLegal(startPos, endPos);
    else if ((whiteQueenBB & startPosBit) != 0 || (blackQueenBB & startPosBit) != 0)
        legal = moveQueenIfLegal(startPos, endPos);
    else if ((whiteKingBB & startPosBit) != 0 || (blackKingBB & startPosBit) != 0)
        legal = moveKingIfLegal(startPos, endPos);
    else
    {
        std::cout << "No piece was moved" << std::endl;
        return false;
    }

    if (!legal)
        return false;

    if (((*currBB == whiteBB ? blackBB : whiteBB) & (baseBit << endPos)) != 0)
        return removeCapturedPiece(endPos);

    endTurn();
    return true;
}

void Board::endTurn()
{
    boardHistory.push_back(Board(this)); // Copies the board into a vector, so that the state can be restored if needed
    ++currentTurn;
    currBB = &((currentTurn & 1) == 0 ? whiteBB : blackBB);
}

void Board::undoMove()
{
    if (boardHistory.size() > 0)
    {
        Board prevBoardState = boardHistory.back();
        boardHistory.pop_back();
        clone(&prevBoardState, this);
    }
    else
    {
        std::cout << "Undo should not have happened, no moves to undo" << std::endl; // For debugging purposes
    }
}

void Board::movePieceOnBB(const std::uint64_t startPos, const std::uint64_t endPos, std::uint64_t &pieceBB)
{
    *currBB += ((baseBit << endPos) - (baseBit << startPos));
    pieceBB += ((baseBit << endPos) - (baseBit << startPos));
    globalBB += ((baseBit << endPos) - (baseBit << startPos));
}

bool Board::movePawnIfLegal(std::uint64_t startPos, std::uint64_t endPos)
{
    std::uint64_t posDiff = endPos > startPos ? endPos - startPos : startPos - endPos;

    // Pawn bitboards are only 48 in size, two rows are never used so they are ommited
    if (((*currBB == whiteBB ? Pawn::getWhiteMoves().at(startPos - 8) : Pawn::getBlackMoves().at(startPos - 8)) & (baseBit << endPos)) == 0)
    {
        std::cout << "Illegal pawn move" << std::endl;
        return false;
    }
    else if (posDiff == 8 && (globalBB & (baseBit << endPos) != 0))
    {
        std::cout << "Attempting to move pawn atop another piece while moving vertically" << std::endl;
        return false;
    }
    else if ((posDiff == 7 || posDiff == 9) && ((*currBB == whiteBB ? blackBB : whiteBB) & (baseBit << endPos)) == 0)
    {
        std::cout << "No piece to capture with pawn" << std::endl;
        return false;
    }

    movePieceOnBB(startPos, endPos, *currBB == whiteBB ? whitePawnBB : blackPawnBB);

    return true;
}

bool Board::moveRookIfLegal(std::uint64_t startPos, std::uint64_t endPos)
{
    if (((Rook::getMoves().at(startPos)) & (baseBit << endPos)) == 0)
    {
        std::cout << "Rook is not moving on a file" << std::endl;
        return false;
    }

    int step = ((endPos - startPos) % 8 == 0) ? (startPos < endPos ? 8 : -8) : (startPos < endPos ? 1 : -1);
    for (std::uint64_t pos = startPos + step; pos != endPos; pos += step)
    {
        if ((globalBB & (baseBit << pos)) != 0)
        {
            std::cout << "There is a piece between the starting and ending positions" << std::endl;
            return false;
        }
    }

    movePieceOnBB(startPos, endPos, (*currBB == whiteBB ? whiteRookBB : blackRookBB));

    return true;
}

bool Board::moveKnightIfLegal(std::uint64_t startPos, std::uint64_t endPos)
{
    if ((Knight::getMoves().at(startPos) & (baseBit << endPos)) == 0)
    {
        std::cout << "Illegal knight move" << std::endl;
        return false;
    }

    movePieceOnBB(startPos, endPos, (*currBB == whiteBB ? whiteKnightBB : blackKnightBB));

    return true;
}

bool Board::moveBishopIfLegal(std::uint64_t startPos, std::uint64_t endPos)
{
    std::uint64_t posDiff = endPos > startPos ? endPos - startPos : startPos - endPos;
    if ((Bishop::getMoves().at(startPos) & (baseBit << endPos)) == 0)
    {
        std::cout << "Illegal bishop move" << std::endl;
        return false;
    }

    // TODO: check no pieces between start & end pos

    movePieceOnBB(startPos, endPos, *currBB == whiteBB ? whiteBishopBB : blackBishopBB);

    return true;
}

bool Board::moveQueenIfLegal(std::uint64_t startPos, std::uint64_t endPos)
{
    return false;
}

bool Board::moveKingIfLegal(std::uint64_t startPos, std::uint64_t endPos)
{
    return false;
}