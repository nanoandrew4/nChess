#!/bin/bash

cd ../../
/home/nanoandrew4/CLion/bin/cmake/linux/bin/cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -G "CodeBlocks - Unix Makefiles" .
/home/nanoandrew4/CLion/bin/cmake/linux/bin/cmake --build cmake-build-release --target nChess -- -j 4