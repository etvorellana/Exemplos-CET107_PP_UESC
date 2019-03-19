
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/* Como compilar

gcc -o run_00-12 -Wall -O3 -fopenmp exemplo_00-12.c
export OMP_SCHEDULE=dynamic,5


*/

int main(){

  int nThread[20];
  int tThreads;
  int j, n = 20;
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
      int nT;
      nT = omp_get_thread_num();
      nThread[nT] = nT;
      if(nT == 0) tThreads = omp_get_num_threads();
      //#pragma omp for
      #pragma omp for ordered
      for(j = 0 ;j < 100; j++){
        x[j] = nT;
        #pragma omp ordered
        {
          if (j%10 != 9)
            printf("%d ", x[j]);
          else
            printf("%d\n", x[j]);
        }
      }
    #endif
  }
  printf("tThreads = %d\n", tThreads);
  return 0;
}
