cmake_minimum_required(VERSION 3.13)
project(nChess)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS_DEBUG "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

include_directories(include)
include_directories(include/pieces)

add_executable(nChess
        include/pieces/Bishop.hpp
        include/pieces/King.hpp
        include/pieces/Knight.hpp
        include/pieces/Pawn.hpp
        include/pieces/Queen.hpp
        include/pieces/Rook.hpp
        include/Board.hpp
        include/UCIParser.hpp
        src/pieces/Bishop.cpp
        src/pieces/King.cpp
        src/pieces/Knight.cpp
        src/pieces/Pawn.cpp
        src/pieces/Queen.cpp
        src/pieces/Rook.cpp
        src/Board.cpp
        src/main.cpp
        src/UCIParser.cpp test/include/Test.h test/src/PieceMovesTest.cpp test/include/PieceMovesTest.h test/src/Test.cpp)
