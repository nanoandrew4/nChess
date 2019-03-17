#pragma once

#include "Board.hpp"

#include <iostream>
#include <string>
#include <cstdint>

class UCIParser
{
public:
  ~UCIParser() = default;

  static bool parse(Board &board, std::string moveStr);

	static bool isPromotionPiece(const char piece);

private:
  static bool notRow(char val);
  static bool notColumn(char val);
};