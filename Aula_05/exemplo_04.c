#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/* Como compilar

gcc -o run_03 -Wall -O3 -fopenmp exemplo_03.c
export OMP_NUM_THREADS=4
*/

int main(){

    int i, x[12];

    #pragma omp parallel
    {
        int nThread;
        #ifdef _OPENMP
            nThread = omp_get_thread_num();
        #else
            nThread = 0;
        #endif

        #pragma omp for
        for(i= 0; i<12; i++)
            x[i] = nThread;
    }

    for(i=0; i<12; i++)
        printf("%d \n", x[i]);
}
