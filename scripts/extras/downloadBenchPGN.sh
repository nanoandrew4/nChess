#!/usr/bin/env bash

# This script downloads a PGN file that can be used for benchmarking as described in the README

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd ${SCRIPT_DIR}
cd ../../

if [[ ! -d "extras/benchmark" ]]
then
    echo "Creating directory nChess/extras/benchmark/"
    mkdir extras
    cd extras
    mkdir benchFiles
    cd benchFiles
fi

echo "Downloading compressed file... Decompressing it is on you!"
wget https://github.com/nanoandrew4/nChess-extras/blob/master/1Mmatches.pgn.bz2