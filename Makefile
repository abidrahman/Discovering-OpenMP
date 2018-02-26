CC : = gcc
CFLAGS : = -g -Wall -fopenmp -lm -std=c99
CFLAGSopenMP : = -g -Wall -fopenmp -lm -std=c99

all: createdata solver

# compile for our macbooks (gcc7)
solver: linearsystemsolver/linearsystemsolver.c dependencies/Lab3IO.c
	gcc-7 $^ $(CFLAGSopenMP) -o solver.o

createdata: dependencies/datagen.c dependencies/Lab3IO.c 
	@gcc $^ -o dependencies/datagen
	@dependencies/datagen

.DEFAULT_GOAL := labmachinesolver

labmachinesolver: linearsystemsolver/linearsystemsolver.c dependencies/Lab3IO.c
	gcc linearsystemsolver/linearsystemsolver.c dependencies/Lab3IO.c -g -Wall -fopenmp -lm -std=c99 -o solver.o

clean:
	@rm -rf *.o
	@rm -rf dependencies/datagen
	@rm -rf logfiles/data_input
	@rm -rf logfiles/data_output

