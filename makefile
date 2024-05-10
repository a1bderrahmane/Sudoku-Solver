CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LDFLAGS =

all: main

main: main.o X.o Sudoku.o
	$(CC) $(LDFLAGS) -o bin/main main.o X.o Sudoku.o

main.o: main.cpp X.h Sudoku.h
	$(CC) $(CFLAGS) -c main.cpp

X.o: X.cpp X.h
	$(CC) $(CFLAGS) -c X.cpp

Sudoku.o: Sudoku.cpp Sudoku.h
	$(CC) $(CFLAGS) -c Sudoku.cpp

clean:
	rm -f bin/*.o bin/main ./*.o

run: all
	./bin/main

valgrind: all
	valgrind --leak-check=full ./bin/main

	debug: CFLAGS += $(DEBUGFLAGS)
debug: clean all

# Run the program with gdb
gdb: debug
	gdb ./bin/main