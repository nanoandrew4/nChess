#include "UCIParser.hpp"

bool UCIParser::parse(Board &board, std::string moveStr)
{
    if (moveStr.length() < 4 || moveStr.length() > 5)
    {
        std::cout << "Move length is invalid" << std::endl;
        return false;
    }
    else if (moveStr.length() == 5 && !isPromotionPiece(moveStr[4]))
    {
        std::cout << "Promotion piece is invalid" << std::endl;
        return false;
    }
    else if (notColumn(moveStr[0]) || notColumn(moveStr[2]) || notRow(moveStr[1]) || notRow(moveStr[3]))
    {
        std::cout << "Entered move is invalid" << std::endl;
        return false;
    }

    std::uint64_t startPos = (7 - (moveStr[0] - 97)) + (8 * (56 - moveStr[1]));
    std::uint64_t endPos = (7 - (moveStr[2] - 97)) + (8 * (56 - moveStr[3]));
    char promotionPiece = ' ';
    if (moveStr.length() == 5)
    {
        promotionPiece = moveStr[4];
        if (promotionPiece < 97)
            promotionPiece += 32; // Make uppercase
    }

    board.makeMove(startPos, endPos, promotionPiece);
    return true;
}

bool UCIParser::isPromotionPiece(char piece)
{
    return piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n';
}

bool UCIParser::notColumn(char val)
{
    return val < 97 || val > 104;
}

bool UCIParser::notRow(char val)
{
    return val < 49 || val > 56;
}