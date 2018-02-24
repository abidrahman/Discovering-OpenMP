
//---------------------------------------------//
// ECE 420 Lab 3
// Abid Rahman and Arjun Kalburgi
// February, 2018
// Filename: linearsystemsolver.h
//		- Header file for the solver
//---------------------------------------------//

#ifndef LINEARSYSTEMSOLVER_H
#define LINEARSYSTEMSOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "./dependencies/Lab3IO.h"
#include "./dependencies/timer.h"

// For threads
int thread_count; 

// For memory and data
int size;
double **Au;
double *X;
int *index;

// For time
double start, end;

void validate_input_args(int argc, char **argv);
void print_usage();
void solve_linear_systems_of_equations(); 

#endif
