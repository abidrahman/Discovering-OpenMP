#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "../dependencies/Lab3IO.h"
#include "../dependencies/timer.h"

int main(int argc, char* argv[]){
    int i, j, k, size;
    int thread_count;
    double** Au;
    double* X;
    int* index;
    double temp;
    double start, end;

    if (argc<=1){   
        printf("Insufficient input!\n");
        return 1;
    }
    thread_count=strtol(argv[1], NULL, 10);

    /*Calculate the solution by serial code*/
    Lab3LoadInput(&Au, &size);
    X = CreateVec(size);
    index = malloc(size * sizeof(int));
    for (i = 0; i < size; ++i)
        index[i] = i;

    GET_TIME(start);
    if (size == 1)
        X[0] = Au[0][1] / Au[0][0];
    else{
        /*Gaussian elimination*/
        #pragma omp parallel num_threads(thread_count) default(none) shared(Au, X, index, size) private(i, j, k, temp)
        {
            for (k = 0; k < size - 1; ++k){
                /*Pivoting*/
                temp = 0;
                j = 0;

                for (i = k; i < size; ++i) {
                    if (temp < Au[index[i]][k] * Au[index[i]][k]) {
                        temp = Au[index[i]][k] * Au[index[i]][k];
                        j = i;
                    }
                }

                #pragma omp single
                {
                    if (j != k) {
                    i = index[j];
                    index[j] = index[k];
                    index[k] = i;
                    }
                
                }
    
                /*calculating*/
                #pragma omp for schedule(dynamic) private(temp, i, j) 
                for (i = k + 1; i < size; ++i){
                    temp = Au[index[i]][k] / Au[index[k]][k];
                    for (j = k; j < size + 1; ++j)
                        Au[index[i]][j] -= Au[index[k]][j] * temp;
                }       
            }
            /*Jordan elimination*/
            for (k = size - 1; k > 0; --k){
                #pragma omp for schedule(dynamic) private(temp, i) 
                for (i = k - 1; i >= 0; --i ){
                    temp = Au[index[i]][k] / Au[index[k]][k];
                    Au[index[i]][k] -= temp * Au[index[k]][k];
                    Au[index[i]][size] -= temp * Au[index[k]][size];
                } 
            }
            /*solution*/
            #pragma omp for schedule(dynamic) private(k)
            for (k=0; k< size; ++k)
                X[k] = Au[index[k]][size] / Au[index[k]][k];
        }
    }
    GET_TIME(end);
    Lab3SaveOutput(X, size, end - start); 

    DestroyVec(X);
    DestroyMat(Au, size);
    free(index);
    return 0;   
}