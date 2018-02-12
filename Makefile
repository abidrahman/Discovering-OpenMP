CC : = gcc
CFLAGS : = -g -Wall -fopenmp -lm -std=c99

all: solver

solver: linearsystemsolver.c
	gcc-7 $^ $(CFLAGS) -o solver.o
	@# $(CC) $^ $(CFLAGS) -o solver.o

.DEFAULT_GOAL := solver

clean:
	@rm -rf *.o
