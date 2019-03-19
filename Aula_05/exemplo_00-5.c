
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/* Como compilar

gcc -o run_00-5 -Wall -O3 -fopenmp exemplo_00-5.c
export OMP_NUM_THREADS=4


*/

int main(){

  int nThread[20];
  int tThreads;
  int i, n = 20;
  //Compilação Condicional
  #ifdef _OPENMP
    nThread[0] = omp_get_thread_num();
    tThreads = omp_get_num_threads();
  #else
    nThread[0] = 0;
    tThreads = 1;
  #endif
  printf("nThread = %d\n", nThread[0]);
  printf("tThreads = %d\n", tThreads);
  printf("---------------------------\n");
  omp_set_num_threads(6);
  #pragma omp parallel if(n > 10) num_threads(10)
  {
    #ifdef _OPENMP
      int nT;
      nT = omp_get_thread_num();
      nThread[nT] = nT;
      if(nT == 0) tThreads = omp_get_num_threads();
    #endif
  }

  for(i = 0; i < tThreads; i++){
    printf("nThreads = %d\n", nThread[i]);
  }
  printf("tThreads = %d\n", tThreads);
  return 0;
}
