# Sudoku Solver

## Overview
This C++ program employs the Dancing Links algorithm, originally devised by Donald Knuth, to solve 9x9 Sudoku puzzles. It efficiently explores all possible solutions and outputs them into a file named `Solution.txt`.

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
