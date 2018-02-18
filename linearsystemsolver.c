
//---------------------------------------------//
// ECE 420 Lab 3
// Abid Rahman and Arjun Kalburgi
// February, 2018
// Filename: linearsystemsolver.c
//		- implement Gauss-Jordan Elimination to solve linear systems of equations
//      - uses OpenMP
//---------------------------------------------//
#include "linearsystemsolver.h"

void validate_input_args(int argc, char **argv) {
    if (argc > 2 || argc <= 1)
    {
        printf("Incorrect number of arguments.\n");
        print_usage();
        exit(EXIT_FAILURE);
    }

    //Get inputs from the user
    thread_count = atoi(argv[1]);
}
void print_usage() {
    printf("USAGE: server <number_of_threads> \n");
}

int main(int argc, char *argv[]) {

    // Valdiate port num and num strings
    validate_input_args(argc, argv);

    // Allocate memory and load the input data for Lab 3
    double** A; 
    double* X; 
    int size; 
    Lab3LoadInput(&A, &size);
    X = CreateVec(size);

    // Solve linear systems of equations
    double start, end;
    GET_TIME(start);
    GET_TIME(end);

    // Save memory and output data 
    Lab3SaveOutput(X, size, (end - start));
    DestroyVec(X);
    DestroyMat(A, size);
    free(indices);

    return 0; 
}