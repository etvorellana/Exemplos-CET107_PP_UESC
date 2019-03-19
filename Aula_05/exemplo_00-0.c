
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/* Como compilar

gcc -o run_00_omp -Wall -O3 -fopenmp exemplo_00-0.c
gcc -o run_00 -Wall -O3 exemplo_00-0.c
*/

int main(){

  int nThread, tThreads;
  //Compilação Condicional
  #ifdef _OPENMP
    nThread = omp_get_thread_num();
    tThreads = omp_get_num_threads();
  #else
    nThread = 4;
    tThreads = 4;
  #endif
  printf("nThread = %d\n", nThread);
  printf("tThreads = %d\n", tThreads);
  printf("---------------------------\n");

  return 0;
}
