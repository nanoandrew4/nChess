cmake_minimum_required(VERSION 3.13)
project(nChess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-O3")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-omit-frame-pointer -D_GLIBCXX_DEBUG")
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
        include/io/UCIParser.hpp
        include/io/MoveReader.h
        src/pieces/Bishop.cpp
        src/pieces/King.cpp
        src/pieces/Knight.cpp
        src/pieces/Pawn.cpp
        src/pieces/Queen.cpp
        src/pieces/Rook.cpp
        src/Board.cpp
        src/main.cpp
        src/io/MoveReader.cpp
        src/io/UCIParser.cpp test/include/Test.h test/src/PieceMovesTest.cpp test/include/PieceMovesTest.h test/src/Test.cpp
        benchmarks/include/PGNRunnerBenchmark.h
        benchmarks/include/MoveReaderBenchmark.h
        benchmarks/include/Benchmark.h
        benchmarks/src/PGNRunnerBenchmark.cpp
        benchmarks/src/MoveReaderBenchmark.cpp
        benchmarks/src/Benchmark.cpp
        )