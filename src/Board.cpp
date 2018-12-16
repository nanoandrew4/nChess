#include "Board.hpp"

#include <bitset>
#include <string>
#include <iostream>

Board::Board()
{
}

Board::~Board()
{
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

std::vector<int> Board::getSetBits(std::uint64_t val)
{
    std::vector<int> setBits;
    for (int i = 0; i < 64; ++i)
        if ((val & (val << i)) != 0)
            setBits.push_back(i);
    return setBits;
}

bool Board::removeCapturedPiece(std::uint64_t piecePos)
{
    std::uint64_t bitPos = (baseBit << piecePos);
    (currBB == whiteBB ? blackBB : whiteBB) -= bitPos;

    if ((bitPos & (currBB == whiteBB ? blackPawnBB : whitePawnBB)) != 0)
        (currBB == whiteBB ? blackPawnBB : whitePawnBB) -= bitPos;
    else if ((bitPos & (currBB == whiteBB ? blackRookBB : whiteRookBB)) != 0)
        (currBB == whiteBB ? blackRookBB : whiteRookBB) -= bitPos;
    else if ((bitPos & (currBB == whiteBB ? blackKnightBB : whiteKnightBB)) != 0)
        (currBB == whiteBB ? blackKnightBB : whiteKnightBB) -= bitPos;
    else if ((bitPos & (currBB == whiteBB ? blackBishopBB : whiteBishopBB)) != 0)
        (currBB == whiteBB ? blackBishopBB : whiteBishopBB) -= bitPos;
    else if ((bitPos & (currBB == whiteBB ? blackQueenBB : whiteQueenBB)) != 0)
        (currBB == whiteBB ? blackQueenBB : whiteQueenBB) -= bitPos;
    else if ((bitPos & (currBB == whiteBB ? blackKingBB : whiteKingBB)) != 0)
    {
        // Undo move that led to king being taken, and continue search
        // Maybe track occurrences to see if it is worth handling some other way
        return false;
    }
    else
    {
        std::cout << "There is no piece to remove..." << std::endl;
        return false;
    }

    return true;
}

bool Board::makeMove(std::uint64_t startPos, std::uint64_t endPos)
{
    if ((whitePawnBB & startPos) != 0 || (blackPawnBB & startPos) != 0)
        movePawnIfLegal(startPos, endPos);
    else if ((whiteRookBB & startPos) != 0 || (blackRookBB & startPos) != 0)
        moveRookIfLegal(startPos, endPos);
    else if ((whiteKnightBB & startPos) != 0 || (blackKnightBB & startPos) != 0)
        moveKnightIfLegal(startPos, endPos);
    else if ((whiteBishopBB & startPos) != 0 || (blackBishopBB & startPos) != 0)
        moveBishopIfLegal(startPos, endPos);
    else if ((whiteQueenBB & startPos) != 0 || (blackQueenBB & startPos) != 0)
        moveQueenIfLegal(startPos, endPos);
    else if ((whiteKingBB & startPos) != 0 || (blackKingBB & startPos) != 0)
        moveKingIfLegal(startPos, endPos);
    else
    {
        std::cout << "No piece was moved" << std::endl;
        return false;
    }

    endTurn();
    return true;
}

bool Board::movePawnIfLegal(std::uint64_t startPos, std::uint64_t endPos)
{
    bool white = currentTurn % 2 == 0;
    int posDiff = (endPos - startPos) * !white ? -1 : 1;

    if (posDiff < 7 || posDiff > 9)
    {
        std::cout << "Pawn move was illegal" << std::endl;
        return false;
    }
    else if ((posDiff == 7 || posDiff == 9) && ((white ? blackBB : whiteBB) & (baseBit << endPos)) == 0)
    {
        std::cout << "No piece to capture" << std::endl;
        return false;
    }

    currBB += ((baseBit << endPos) - (baseBit << startPos));
    white ? whitePawnBB : blackPawnBB += ((baseBit << endPos) - (baseBit << startPos));

    if (posDiff == 7 || posDiff == 9)
        return removeCapturedPiece(endPos);
    return true;
}

bool Board::moveRookIfLegal(std::uint64_t startPos, std::uint64_t endPos)
{
    if ((endPos - startPos) % 8 != 0 || ((endPos / 8) - (startPos / 8)) != 0)
    {
        std::cout << "Rook is not moving on a file" << std::endl;
        return false;
    }

    int step = ((endPos - startPos) % 8 == 0) ? (startPos < endPos ? 8 : -8) : (startPos < endPos ? 1 : -1);
    for (std::uint64_t pos = startPos; pos != endPos; pos += step)
    {
        if ((currBB & (baseBit << pos)) != 0)
        {
            std::cout << "There is a piece between the starting and ending positions" << std::endl;
            return false;
        }
    }

    if (((currBB == whiteBB ? blackBB : whiteBB) & (baseBit << endPos)) != 0)
        return removeCapturedPiece(endPos);
    return true;
}