
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/* Como compilar

gcc -o run_00-6 -Wall -O3 -fopenmp exemplo_00-6.c
export OMP_NUM_THREADS=4


*/

int main(){

  int nThread[20];
  int tThreads;
  int i, n = 20;
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
  #pragma omp parallel if(n > 10) num_threads(10)
  {
    #ifdef _OPENMP
      int nT, j;
      nT = omp_get_thread_num();
      nThread[nT] = nT;
      if(nT == 0) tThreads = omp_get_num_threads();
      //for(j = 10*nT;j < 10*(nT+1) ; j++){
      for(j = 0 ;j < 10; j++){
        //x[j] = nT;
        x[j + (nT*10)] = nT;
      }
    #endif
  }
  int j;
  for(i = 0; i < tThreads; i++){
    printf("nThreads = %d\n", nThread[i]);
    for(j = 0; j < 10; j++){
      printf("%d ", x[j + (i*10)]);
    }
    printf("\n");
  }
  printf("tThreads = %d\n", tThreads);
  return 0;
}
