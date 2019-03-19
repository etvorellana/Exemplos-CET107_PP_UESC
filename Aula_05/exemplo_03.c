#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/* Como compilar

gcc -o run_03 -Wall -O3 -fopenmp exemplo_03.c
export OMP_NUM_THREADS=4
*/

int main(){

    int i, x[12];

    #pragma omp parallel private(i)
    {
        int nThread, tThreads, tam;
        #ifdef _OPENMP
            nThread = omp_get_thread_num();
            tThreads = omp_get_num_threads();
        #else
            nThread = 0;
            tThreads = 1;
        #endif
        tam = 12 / tThreads;

        for(i= nThread*tam; i<(nThread + 1)*tam; i++)
            x[i] = nThread;
    }

    for(i=0; i<12; i++)
        printf("%d \n", x[i]);
}
