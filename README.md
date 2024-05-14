# Sudoku Solver

## Overview
This C++ program employs the Dancing Links algorithm, originally devised by Donald Knuth, to solve 9x9 Sudoku puzzles. It efficiently explores all possible solutions and outputs them into a file named `Solution.txt`.

## Dancing Links Algorithm

The Dancing Links algorithm, also known as DLX, is a computer science algorithm that is used to solve exact cover problems. It was developed by Donald Knuth and is particularly well-suited for solving Sudoku puzzles.
For more information, you can visit the [Wikipedia page](https://en.wikipedia.org/wiki/Dancing_Links) for the Dancing Links algorithm.

## Features
- **Algorithm**: Utilizes Donald Knuth's Dancing Links algorithm, an efficient method for backtracking solutions to combinatorial problems.
- **Output**: All found solutions are saved to `Solution.txt`.

## Getting Started
To compile and run the Sudoku Solver, follow these instructions:

### Prerequisites
- GNU Make.
- GDB for debugging (optional).
- Valgrind for memory leak detection (optional).

### Compilation
Use the `make` command to compile the project:
```bash
make
```

### Running the Program
Use the `make run` command to compile and run the project:
```bash
make run
```

### Debugging
To debug the program using GDB:
```bash
make gdb
```

### Memory Leak Check
To check for memory leaks with Valgrind:
```bash
make valgrind
```

## Testing
The program is tested on the following Sudoku puzzle:
![Sudoku Puzzle](exampleSudoku.jpg)

The output of the program is printed in the `Solution.txt` file.
