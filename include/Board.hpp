#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>

#include "pieces/Rook.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"

class Board
{

public:
  Board() = default;
  Board(const Board *b);
  ~Board() = default;

  static void visDebug(std::uint64_t board);
  void displayBoard();

  bool makeMove(const std::uint64_t startPos, const std::uint64_t endPos);

  int getCurrentTurn() { return currentTurn; }

private:
  /* 
   * All positions are little-endian. These values set the inital positions for the bit boards
   */
  std::uint64_t globalBB = 0xffff00000000ffff;

  std::uint64_t whiteBB = 0x000000000000ffff;
  std::uint64_t blackBB = 0xffff000000000000;

  std::uint64_t whitePawnBB = 0x000000000000ff00;
  std::uint64_t whiteKnightBB = 0x0000000000000042;
  std::uint64_t whiteBishopBB = 0x0000000000000024;
  std::uint64_t whiteRookBB = 0x0000000000000081;
  std::uint64_t whiteQueenBB = 0x0000000000000010;
  std::uint64_t whiteKingBB = 0x0000000000000008;

  std::uint64_t blackPawnBB = 0x00ff000000000000;
  std::uint64_t blackKnightBB = 0x4200000000000000;
  std::uint64_t blackBishopBB = 0x2400000000000000;
  std::uint64_t blackRookBB = 0x8100000000000000;
  std::uint64_t blackQueenBB = 0x1000000000000000;
  std::uint64_t blackKingBB = 0x0800000000000000;

  int currentTurn = 0;

  const static std::uint64_t baseBit = 1;
  std::uint64_t *currBB = &whiteBB;

  std::vector<Board> boardHistory;

  void clone(const Board *src, Board *dest);

  static void loadPiecesToVisBoard(std::vector<std::string> &board, const std::uint64_t bitBoard, const std::string displayValue);

  static std::vector<std::uint64_t> getSetBits(const std::uint64_t val);
  bool removeCapturedPiece(const std::uint64_t piecePos);

  void endTurn();
  void undoMove();

  bool isLeavingKingInCheck();

  bool movePawnIfLegal(const std::uint64_t startPos, const std::uint64_t endPos);
  bool moveRookIfLegal(const std::uint64_t startPos, const std::uint64_t endPos);
  bool moveKnightIfLegal(const std::uint64_t startPos, const std::uint64_t endPos);
  bool moveBishopIfLegal(const std::uint64_t startPos, const std::uint64_t endPos);
  bool moveQueenIfLegal(const std::uint64_t startPos, const std::uint64_t endPos);
  bool moveKingIfLegal(const std::uint64_t startPos, const std::uint64_t endPos);

  void movePieceOnBB(const std::uint64_t startPos, const std::uint64_t endPos, std::uint64_t &pieceBB);
};