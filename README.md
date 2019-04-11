# nChess
Really just another chess engine, since I read about bitboards and thought it would be fun to try my hand at an 
implementation (given that my previous chess engine was not great). Active development currently paused for studies,
but will be continued as soon as those end.

## Compilation:
To compile the program, you can use the script located at 
[scripts/build/build-release.sh](https://github.com/nanoandrew4/nChess/blob/master/scripts/build/build-release.sh). 
The program will be built at the project root, inside a new directory called 'build/release'. It will attempt to use
clang to compile, so if you do not have clang available on your system, you can change the compiler by modifying the 
build script (this should be a simple change at the top of the script). c++17 features are used throughout the code,
so make sure you are rocking a relatively new version of your compiler.

## Use:
Currently the program simply allows you to enter moves, and play against yourself, while checking the legality of 
the various moves before executing the move. Although the end goal is to have a full fledged chess engine, the work 
on the project up until now has focused mainly on getting a fast legality checking mechanism that the engine will 
employ to search and evaluate moves.

To simply play a game against yourself, run the command './nChess play'.


### Benchmarking:
It is also possible to benchmark the legality evaluator, by feeding it a PGN file containing UCI moves. 
Unfortunately the benchmark suite is not built for flexibility, so it is very picky as to how moves, matches and the 
file in general is formatted. A sample benchmarking file can be downloaded, although it is rather large in size, so 
it does not form part of this repository. Instructions on how to use your own PGN files are available further on in the 
document.

There are two types of benchmarks currently available. The first is the aforementioned legality evaluator, which has
the type 'move'. This benchmark must be followed by the file to use for benchmarking, which must be appropriately 
formatted. The other benchmark is for benchmarking PGN file read speed, and has the type 'fileread'. This benchmark 
must also be supplied with a PGN file to read from, with the same format as the file required for the legality 
evaluation benchmark.

To run the benchmarks, run the command './nChess bench {benchmarkType} {benchmarkFile}'. For example, if making use 
of the sample file that can be downloaded using 
[scripts/extras/downloadBenchPGN.sh](https://github.com/nanoandrew4/nChess/tree/master/scripts/extras), the command 
for benchmarking the legality evaluator would be './nChess bench move extras/benchmark/megaChessDB.pgn'

Additionally, the '--last-core' flag could be supplied after the executable, and before the benchmark type, to run 
the benchmarks on the last core available. This can be useful for getting consistent results, especially if the last 
core is disabled so the OS cannot make use of it, and it can be used exclusively by this program. A script to disable
(and re-enable) the last core of the CPU is available in the [scripts/bench/](https://github.com/nanoandrew4/nChess/tree/master/scripts/bench) 
folder (for Linux only, use at your own peril, after each script is run the machine must be rebooted).

### Testing:
The program also has a test suite to run a PGN file through to find invalid moves (or bugs in the legality evaluator,
 which is its actual purpose). To make use of the test suite, which will report errors on a case by case basis, run
 the following command './nChess test --smove 0 --smatch 0 --path /path/to/pgn/file'. The test suite makes use of the 
 same file format as the benchmarking suite, so make sure that the file has been converted and formatted properly 
 before feeding it to the program.
 
Here is a brief explanation of the parameters that can be passed to the test suite:
- --smove: Move number from which to start stepping through each move individually. Useful for determining the cause 
of an error, as you can see the moves leading up to it.
- --smatch: Match number from which to start stepping through each move individually. Useful for determining the cause
of an error, as you can see the moves leading up to it.
- --path: Path to the UCI PGN file to read moves from, to test the legality evaluator.

If --smove and --smatch are set to 0, the test suite will not step through moves at any point, it will just do a full
 run of the test file, and output the results at the end.

### How to use custom PGN files for benchmarking

Find yourself a nice PGN file that you wish to use for benchmarking. Make sure it contains at least several thousand 
games, otherwise the benchmark may show skewed results. Now go download and compile (if necessary):
[pgn-extract](https://www.cs.kent.ac.uk/people/staff/djb/pgn-extract/). Run the program on your PGN file with
the following flags: '-Wuci -s --noresults --nocomments --nobadresults'. Depending on your file size, this may take a
while. Once that is done, run [scripts/cleanupUCIFile.awk](https://github.com/nanoandrew4/nChess/blob/master/scripts/cleanupUCIFile.awk) 
on the file that pgn-extract created, and pipe that output into a new file. This final file is what may be used for 
running the benchmark suite. 

If your file should not work, you have replicated the steps correctly and have verified that the file is in fact 
valid, go ahead and open an issue so the matter can be resolved.