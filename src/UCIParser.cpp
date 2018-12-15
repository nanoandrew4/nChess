#include "UCIParser.hpp"

bool UCIParser::parse(std::string moveStr)
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

    int startPos = (moveStr[0] - 97) + (8 * (moveStr[1] - 1));
    int endPos = (moveStr[2] - 97) + (8 * (moveStr[3] - 1));

    // Make move

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