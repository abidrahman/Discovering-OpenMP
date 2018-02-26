#include "linearsystemsolver.h"

int main(int argc, char *argv[])
{
    thread_count = 2; 

    /*Calculate the solution by serial code*/
    Lab3LoadInput(&Au, &size);
    X = CreateVec(size);
    indices = malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
        indices[i] = i;

    GET_TIME(start);
    solve_linear_systems_of_equations(); 
    GET_TIME(end);
    Lab3SaveOutput(X, size, end - start);

    DestroyVec(X);
    DestroyMat(Au, size);
    free(indices);
    return 0;
}

void solve_linear_systems_of_equations()
{
    int i, j, k;
    double temp;

    if (size == 1)
        X[0] = Au[0][1] / Au[0][0];
    else
    {
        /*Gaussian elimination*/
        for (k = 0; k < size - 1; ++k)
        {
            /*Pivoting*/
            temp = 0;
            for (i = k, j = 0; i < size; ++i)
                if (temp < Au[indices[i]][k] * Au[indices[i]][k])
                {
                    temp = Au[indices[i]][k] * Au[indices[i]][k];
                    j = i;
                }
            if (j != k) /*swap*/
            {
                i = indices[j];
                indices[j] = indices[k];
                indices[k] = i;
            }
                /*calculating*/
#pragma omp parallel for num_threads(thread_count) default(none) shared(Au, indices, k, size) private(i, j, temp)
            for (i = k + 1; i < size; ++i)
            {
                temp = Au[indices[i]][k] / Au[indices[k]][k];
                for (j = k; j < size + 1; ++j)
                    Au[indices[i]][j] -= Au[indices[k]][j] * temp;
            }
        }
        /*Jordan elimination*/
        for (k = size - 1; k > 0; --k)
        {
            for (i = k - 1; i >= 0; --i)
            {
                temp = Au[indices[i]][k] / Au[indices[k]][k];
                Au[indices[i]][k] -= temp * Au[indices[k]][k];
                Au[indices[i]][size] -= temp * Au[indices[k]][size];
            }
        }
        /*solution*/
        for (k = 0; k < size; ++k)
            X[k] = Au[indices[k]][size] / Au[indices[k]][k];
    }
}