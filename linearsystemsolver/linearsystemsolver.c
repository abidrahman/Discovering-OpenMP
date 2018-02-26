
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

    // Gaussian elimination
    int temp, j = 0;
    int i, k;
    // # pragma omp parallel for num_threads(thread_count) default(none) shared(Au, indices, k, size) 
    for (k = 0; k < size - 1; ++k)
    {

        # pragma omp single
        {
            // # pragma omp parallel for num_threads(thread_count) default(none) shared(Au, indices, k, size) private(i)
            for (i = k; i < size; ++i) {
                if (temp < Au[indices[i]][k] * Au[indices[i]][k]) {

                    # pragma omp critical
                    { 
                        if (temp < Au[indices[i]][k] * Au[indices[i]][k]){
                            temp = Au[indices[i]][k] * Au[indices[i]][k];
                            j = i;
                        }
                    }
                }
            }

            // Swap
            if (j != k) {
                i = indices[j];
                indices[j] = indices[k];
                indices[k] = i;
            }
            
            // calculation step
            # pragma omp parallel for num_threads(thread_count) default(none) shared(Au, indices, k, size) private(i, j, temp) schedule (static, 10)
            for (i = k + 1; i < size; ++i) {
                temp = Au[indices[i]][k] / Au[indices[k]][k];

                //#pragma omp parallel for num_threads(thread_count) default(none) shared(Au, indices, k, size) private(j)
                for (j = k; j < size + 1; ++j) {
                    Au[indices[i]][j] -= Au[indices[k]][j] * temp;
                }
            }
        }
 	}
    
    
    // Jordan elimination
    // # pragma omp parallel for num_threads(thread_count) default(none) shared(Au, indices, k, size) private(k) 
    for (k = size - 1; k > 0; --k) {

        // # pragma omp parallel for num_threads(thread_count) default(none) shared(Au, indices, k, size) private(temp)	 
        for (i = k - 1; i >= 0; --i) {
            temp = Au[indices[i]][k] / Au[indices[k]][k];
            Au[indices[i]][k] -= temp * Au[indices[k]][k];
            Au[indices[i]][size] -= temp * Au[indices[k]][size];
        } 
    }
        
    # pragma omp parallel for num_threads(thread_count) default(none) shared(X, Au, size, index) private(k) schedule (static, 10)
    for (k=0; k < size; ++k) {
        X[k] = Au[indices[k]][size] / Au[indices[k]][k];
        // printf("%e\n", X[k]);
 	}

    GET_TIME(end);
}

int main(int argc, char *argv[]) {

    // Valdiate port num and num strings
    // validate_input_args(argc, argv);

    // Set thread number
    thread_count = 2; 
    omp_set_num_threads(thread_count);

    // Allocate memory and load the input data for Lab 3
    Lab3LoadInput(&Au, &size);
    X = CreateVec(size);

    // Assign indices with open mp
    indices = malloc(size * sizeof(int));
    int i; 
    # pragma omp parallel for num_threads(thread_count) shared(indices, size) private(i)
    for (i = size-1; i > 0; --i)
        indices[i] = i;

    // Solve linear systems of equations
    if (size == 1) {
        GET_TIME(start);
        X[0] = Au[0][1] / Au[0][0];
        GET_TIME(end);
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
