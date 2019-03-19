
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/* Como compilar

gcc -o run_00-8 -Wall -O3 -fopenmp exemplo_00-8.c
export OMP_NUM_THREADS=4


*/

int main(){

  int nThread[20];
  int tThreads;
  int i, j, n = 20;
  int x[100];
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
  #pragma omp parallel if(n > 10) num_threads(7)
  {
    #ifdef _OPENMP
      int nT;
      nT = omp_get_thread_num();
      nThread[nT] = nT;
      if(nT == 0) tThreads = omp_get_num_threads();
      #pragma omp for schedule(static,5)
      for(j = 0 ;j < 100; j++){
        x[j] = nT;
      }
    #endif
  }
  /*for(i = 0; i < tThreads; i++){
    printf("nThreads = %d\n", nThread[i]);
    for(j = 0; j < 10; j++){
      printf("%d ", x[j + (i*10)]);
    }
    printf("\n");
  }*/
  for(j = 0; j < 10; j++){
    for(i=0; i<10; i++)
      printf("%d ", x[i+j]);
    printf("\n");
  }
  printf("tThreads = %d\n", tThreads);
  return 0;
}
