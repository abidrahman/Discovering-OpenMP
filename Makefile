CC : = gcc
CFLAGS : = -g -Wall -fopenmp -lm -std=c99
CFLAGSopenMP : = -g -Wall -fopenmp -lm -std=c99

all: createdata solver

solver: linearsystemsolver.c dependencies/Lab3IO.c
	gcc-7 $^ $(CFLAGSopenMP) -o solver.o

createdata: dependencies/datagen.c dependencies/Lab3IO.c 
	@gcc $^ -o dependencies/datagen
	@dependencies/datagen

.DEFAULT_GOAL := solver

clean:
	@rm -rf *.o
	@rm -rf dependencies/datagen

