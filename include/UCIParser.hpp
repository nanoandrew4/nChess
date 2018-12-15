#pragma once

#include <iostream>
#include <string>

class UCIParser
{
  public:
    ~UCIParser() = default;

    static bool parse(std::string moveStr);

  private:
    static bool isPromotionPiece(char piece);
    static bool notRow(char val);
    static bool notColumn(char val);
};