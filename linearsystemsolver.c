
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

//  /*Gaussian elimination*/
    // SHOULD ADD AN OMP BEFORE FOR LOOP: #pragma omp parallel
// 	for (int k = 0; k < size - 1; ++k) {
    
    // CAN HAVE AN OMP SINGLE ENCOMPASING REST OF GAUSSIAN ELIM #pragma omp single
// 	    /*Pivoting*/
// 	    int temp = 0;
// 	    int j = 0;
// 	    # pragma omp parallel for private(i)
// 	    for (int i = k; i < size; ++i) {
// 	       if (temp < Au[indices[i]][k] * Au[indices[i]][k]){
//                  # pragma omp critical
//                  { 
//                     if (temp < Au[indices[i]][k] * Au[indices[i]][k]){
//                         temp = Au[indices[i]][k] * Au[indices[i]][k];
//                         j = i;
//                     }
//                  }
// 			}
//         }


// 	    if (j != k)/*swap*/{
// 			int i = indices[j];
// 			indices[j] = indices[k];
// 			indices[k] = i;
// 	    }
        
// 	    /*calculating*/
// 	    #pragma omp parallel for private(i,temp,j)
// 	    for (int i = k + 1; i < size; ++i){
// 	        temp = Au[indices[i]][k] / Au[indices[k]][k];
// 	        for (j = k; j < size + 1; ++j) {
// 	            Au[indices[i]][j] -= Au[indices[k]][j] * temp;
// 			}
// 	    }   
// 	}
//     /*Jordan elimination*/
    // CAN HAVE AN OMP PARALLEL BEFORE THIS FOR LOOP TOO
//     for (int k = size - 1; k > 0; --k){
//      #pragma omp parallel for private(temp)	
//         for (int i = k - 1; i >= 0; --i ){
//             temp = Au[indices[i]][k] / Au[indices[k]][k];
//             Au[indices[i]][k] -= temp * Au[indices[k]][k];
//             Au[indices[i]][size] -= temp * Au[indices[k]][size];
//         } 
//     }
//         /*solution*/
// 	#pragma omp parallel for
//         for (int k=0; k< size; ++k) {
//             X[k] = Au[indices[k]][size] / Au[indices[k]][k];
// 	    printf("%e\n", X[k]);
// 	}

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

    // Assign indices with open mp
    indices = malloc(size * sizeof(int));
    #pragma omp for
    for (int i = 0; i < size; ++i)
        indices[i] = i;

    // Solve linear systems of equations
    if (size == 1) {
        X[0] = Au[0][1] / Au[0][0];
    } else {
        solve_linear_systems_of_equations(); 
    }

    // Save memory and output data 
    Lab3SaveOutput(X, size, (end - start));
    DestroyVec(X);
    DestroyMat(Au, size);
    free(indices);

    return 0; 
}