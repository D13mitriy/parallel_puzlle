# Parallel Puzzle Solver

This project implements a parallelized C++ program to solve the "largest sequence puzzle." The program constructs a sequence of numbers based on matching the last two digits of one number with the first two digits of another.

## Features
- **Parallel Processing**: Utilizes multi-threading to speed up computations.
- **Flexible Input**: Reads numbers from a text file (`source0.txt`) where each line contains a single number.
- **CMake Build System**: Compatible with all major platforms (Linux, macOS, Windows).

## Input Format
The input file should be a plain text file where each line contains a numeric value. Example:

## Requirements
- C++17 or later
- CMake (version 3.16 or later)
- GCC, Clang, or MSVC compiler with thread support

## Compilation
1. Clone the repository:
   
   git clone https://github.com/yourusername/parallel_puzzle.git
   cd parallel_puzzle

2. Create a build directory and compile the program:

mkdir build
cd build
cmake ..
cmake --build .

## Usage

Run the program with the input file and specify the number of threads:

./parallel_puzzle source0.txt 4

## Example Output

Using 4 threads.
Largest sequence: 24846080177092
Execution Time: 102 ms
