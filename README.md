# nChess
Really just another chess engine, since I read about bitboards and thought it would be fun to try my hand at an 
implementation (given that my previous chess engine was not great). Active development currently paused for studies, but will be continued as soon as those end.

---

## Compilation:
To compile the program, simply run the build script in the build directory. This should yield an executable file in 
the build directory, that was built using the 'Release' target. Other profiles are available, but the aforementioned one should be preferred.

## Use:
Currently the program simply allows you to enter moves, and play against yourself, while checking the legality of 
the various moves before executing the move. Although the end goal is to have a full fledged chess engine, the work on the project up until now has focused mainly on getting a fast legality checking mechanism that the engine will employ to search and evaluate moves.

To simply play a game against yourself, run the command './nChess play'.

It is also possible to benchmark the legality evaluator, by feeding it a PGN file containing UCI moves. 
Unfortunately the benchmark suite is not built for flexibility, so it is very picky as to how moves, matches and the file in general is formatted. A sample benchmarking file can be downloaded, although it is rather large in size, so it does not form part of this repository. Instructions on how to use your own PGN files are available further on in the document.

There are two types of benchmarks currently available. The first is the aforementioned legality evaluator, which has
the type 'move'. This benchmark must be followed by the file to use for benchmarking, which must be appropriately formated. The other benchmark is for benchmarking PGN file read speed, and has the type 'fileread'. This benchmark must also be supplied with a PGN file to read from, with the same format as the file required for the legality evaluation benchmark.

To run the benchmarks, run the command './nChess bench {benchmarkType} {benchmarkFile}'. For example, if making use 
of the sample file that can be downloaded using [script], the command for benchmarking the legality evaluator would 
be './nChess bench move resources/megaChessDB.pgn'

Additionally, the '--last-core' flag could be supplied after the executable, and before the benchmark type, to run 
the benchmarks on the last core available. This can be useful for getting consistent results, especially if the last 
core is disabled so the OS cannot make use of it, and it can be used exclusively by this program. A script to disable
(and re-enable) the last core of the CPU is available in the scripts/bench/ folder (for Linux only, use at your own 
peril, after each script is run the maching must be rebooted).

### How to use custom PGN files for benchmarking