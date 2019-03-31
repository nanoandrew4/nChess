#!/usr/bin/env bash

# Generates a Profiling executable using profile guided optimization
# Requires perf, cmake v3.13.x, clang, lld, autofdo

cd ../../cmake-build-profiling
echo "Starting initial compilation"

cmake -DCMAKE_BUILD_TYPE=Profiling -DENABLE_PGO=Off -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -G "CodeBlocks - Unix Makefiles" ../
cmake --build . --target clean -- -j 4
cmake --build . --target all -- -j 4

printf "\n\n"
echo "Profiling produced binary, requires superuser privileges in order to record using perf"
sudo perf record -b -F 20000 ./nChess --last-core bench move ../megaChessDB.pgn
sudo chmod 777 perf.data

printf "\n\n"
echo "Creating LLVM profile data for use in next compilation pass"
create_llvm_prof --binary=./nChess --out=nChess-prof.prof

echo "Compiling using Profile Guided Optimization, based on the recently produced profile"
cmake -DCMAKE_BUILD_TYPE=Profiling -DENABLE_PGO=On -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -G "CodeBlocks - Unix Makefiles" ../
cmake --build . --target clean -- -j 4
cmake --build . --target all -- -j 4

printf "\n\n"
echo "Finished building optimized executable"