#!/usr/bin/env bash

# Generates a Release executable using profile guided optimization
# Requires perf, cmake v3.13.x, clang, lld, autofdo

# Compiler to use, defaults to clang, but can be modified
C_COMPILER=clang
CXX_COMPILER=clang++

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd ${SCRIPT_DIR}
cd ../../

if [[ ! -d "build/" ]]
then
    echo "Creating build directory at project root"
    mkdir build
fi

if [[ ! -d "build/release/" ]]
then
    echo "Creating release target directory at build/"
    mkdir build/release
fi

cd build/release
echo "Compiling with ${CXX_COMPILER}... This can be changed by modifying this build script"
echo "This program requires some c++17 features, so make sure you have a relatively up to date compiler"

cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_PGO=Off -DCMAKE_C_COMPILER=${C_COMPILER} -DCMAKE_CXX_COMPILER=${CXX_COMPILER} -G "CodeBlocks - Unix Makefiles" ../../
cmake --build . --target clean -- -j 4
cmake --build . --target all -- -j 4

#printf "\n\n"
#echo "Profiling produced binary, requires superuser privileges in order to record using perf"
#sudo perf record -b -F 20000 ./nChess --last-core bench move ../megaChessDB.pgn
#sudo chmod 777 perf.data

#printf "\n\n"
#echo "Creating LLVM profile data for use in next compilation pass"
#create_llvm_prof --binary=./nChess --out=nChess-rel.prof

#echo "Compiling using Profile Guided Optimization, based on the recently produced profile"
#cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_PGO=On -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -G "CodeBlocks - Unix Makefiles" ../
#cmake --build . --target clean -- -j 4
#cmake --build . --target all -- -j 4

#printf "\n\n"
#echo "Finished building optimized executable"