
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
void solve_linear_systems_of_equations() {
    GET_TIME(start);
    // BASELINE SOLUTION: 
    // NEED TO ENSURE OPENMP WORKS FIRST

//     if (size == 1)
//         X[0] = Au[0][1] / Au[0][0];
//     else
//     {
//         /*Gaussian elimination*/
//         for (k = 0; k < size - 1; ++k)
//         {
//             /*Pivoting*/
//             int temp = 0;
//             for (i = k, j = 0; i < size; ++i)
//                 if (temp < Au[index[i]][k] * Au[index[i]][k])
//                 {
//                     temp = Au[index[i]][k] * Au[index[i]][k];
//                     j = i;
//                 }
//             if (j != k) /*swap*/
//             {
//                 i = index[j];
//                 index[j] = index[k];
//                 index[k] = i;
//             }
//                 /*calculating*/
//            #pragma omp parallel for num_threads(thread_count) default(none) shared(Au, index, k, size) private(i, j, temp)
//             for (i = k + 1; i < size; ++i)
//             {
//                 temp = Au[index[i]][k] / Au[index[k]][k];
//                 for (j = k; j < size + 1; ++j)
//                     Au[index[i]][j] -= Au[index[k]][j] * temp;
//             }
//         }
//         /*Jordan elimination*/
//         for (k = size - 1; k > 0; --k)
//         {
//             for (i = k - 1; i >= 0; --i)
//             {
//                 temp = Au[index[i]][k] / Au[index[k]][k];
//                 Au[index[i]][k] -= temp * Au[index[k]][k];
//                 Au[index[i]][size] -= temp * Au[index[k]][size];
//             }
//         }
//         /*solution*/
//         for (k = 0; k < size; ++k)
//             X[k] = Au[index[k]][size] / Au[index[k]][k];
//     }
    GET_TIME(end);
}

int main(int argc, char *argv[]) {

    // Valdiate port num and num strings
    validate_input_args(argc, argv);

    // Set thread number
    // omp_set_num_threads(thread_count);

    // Allocate memory and load the input data for Lab 3
    Lab3LoadInput(&Au, &size);
    X = CreateVec(size);

    // Assign index with open mp
    index = malloc(size * sizeof(int));
    #pragma omp for
    for (int i = 0; i < size; ++i)
        index[i] = i;

    // Solve linear systems of equations
    solve_linear_systems_of_equations(); 

    // Save memory and output data 
    Lab3SaveOutput(X, size, (end - start));
    DestroyVec(X);
    DestroyMat(Au, size);
    free(index);

    return 0; 
}