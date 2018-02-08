CC : = gcc
CFLAGS : = -g -Wall -fopenmp -lm -std=c99

all: solver

solver: linearsystemsolver.c
	@$(CC) $^ $(CFLAGS) -o solver.o

clean:
	@rm -rf *.o
