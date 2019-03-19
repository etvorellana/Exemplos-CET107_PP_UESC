
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/* Como compilar

gcc -o run_00-1_omp -Wall -O3 -fopenmp exemplo_00-1.c
gcc -o run_00-1 -Wall -O3 exemplo_00-1.c


*/

int main(){

  int nThread[20];
  int tThreads;
  int i;
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
  #pragma omp parallel
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
