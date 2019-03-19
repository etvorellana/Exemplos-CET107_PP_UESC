#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define MSIZE 10000

/* Como compilar

gcc -o run_05 -Wall -O3 -fopenmp exemplo_05.c
export OMP_NUM_THREADS=4
*/

int main(void)
{
  int i,j;
  int mSize = MSIZE;
  int nSize[MSIZE];
  double **x;
  double soma[MSIZE];
  double somaT = 0.0;
  double start, end, tSerial;

  //Alocação e inicialização
  x = (double **) malloc(mSize*sizeof(double *));
  srandom(123456789);
  for(i = 0; i < mSize; i++)
  {
    nSize[i] = random() % (mSize+1);
    x[i] = (double *) malloc(nSize[i] * sizeof(double));
    for(j = 0; j < nSize[i]; j++)
    {
      x[i][j] = (double)random()/RAND_MAX;
    }
  }

  //Cálculo
  start = omp_get_wtime();
  for(i = 0; i < mSize; i++){
    soma[i] = 0.0;
    for(j = 0; j < nSize[i]; j++){
      soma[i] += x[i][j];
    }
    somaT += soma[i];
  }
  end = omp_get_wtime();
  tSerial = end - start;

  //Resultados
  printf("Processamento 1 - %f\n", tSerial/double(mSize*mSize));
  printf("-> %f \n", somaT);

  //Fechando tudo
  for(i = 0; i < mSize; i++){
    free(x[i]);
  }
  free(x);

}
