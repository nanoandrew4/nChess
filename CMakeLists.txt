cmake_minimum_required(VERSION 3.13)
project(nChess)

set(CMAKE_CXX_STANDARD 17)

# Target for debugging, enables debug messages from the program
set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-omit-frame-pointer -DVISUAL_BECHMARK -DPRINT_DEBUG_MESSAGES")

# Target for debugging with GDB, in order to be able to view string values
#set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-omit-frame-pointer -D_GLIBCXX_DEBUG")

# Target for optimal runtime performance and maintaining full functionality
if (ENABLE_PGO)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fuse-ld=lld -flto=full -gline-tables-only -march=native
    -fprofile-sample-use=nChess-rel.prof -DVISUAL_BECHMARK")
else ()
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fuse-ld=lld -flto=full -gline-tables-only -DVISUAL_BECHMARK -march=native")
endif ()

# Target for performance testing, silences and removes benchmark data gathering, so as to run benchmarks as fast as
# possible
if (ENABLE_PGO)
    set(CMAKE_CXX_FLAGS_PROFILING "-O3 -fuse-ld=lld -flto=full -fno-omit-frame-pointer -march=native
    -gline-tables-only -fprofile-sample-use=nChess-prof.prof")
else ()
    set(CMAKE_CXX_FLAGS_PROFILING "-O3 -fuse-ld=lld -flto=full -fno-omit-frame-pointer -g -march=native")
    #    set(CMAKE_CXX_FLAGS_PROFILING "-O3 -fuse-ld=lld -flto=full -gline-tables-only -fno-omit-frame-pointer")
endif ()


# Common compiler flags for all targets
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
        src/io/UCIParser.cpp include/test/Test.h src/test/PieceMovesTest.cpp include/test/PieceMovesTest.h src/test/Test.cpp
        include/benchmark/BoardMoveBenchmarks.h
        include/benchmark/MoveReaderBenchmark.h
        include/benchmark/Benchmark.h
        src/benchmark/BoardMoveBenchmarks.cpp
        src/benchmark/MoveReaderBenchmark.cpp
        src/benchmark/Benchmark.cpp
        )