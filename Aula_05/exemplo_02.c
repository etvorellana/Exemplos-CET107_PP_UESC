#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100


int main(int argc, char *argv[]) {

  double *x, *y;
  int i,j;
  int nSize;
  double sumX,sumY;
  double start, end, tSerial[3];

  if (argc >= 2)
    nSize = atoi(argv[1]);
  else
    nSize = 100;

  srandom(123456789);

  sumX = sumY = 0;

  x = (double *) malloc(nSize * sizeof (double));
  y = (double *) calloc(nSize, sizeof (double));

  // Entrada de dados
  for(i = 0; i < nSize; i++)
    x[i] = (double)random()/RAND_MAX;

  // Processamento 1
  start = omp_get_wtime();
  for (i = 0; i < nSize; i++){
    for(j = 0; j <= i; j++)
      y[i] += x[j];
    y[i] /= (i+1);
  }
  end = omp_get_wtime();
  tSerial[0] = end - start;
  printf("Processamento 1 - %f\n", tSerial[0]);
  fflush( stdout );

  // Processamento 2
  start = omp_get_wtime();
  for (i = 0; i < nSize; i++)
    x[i] += y[i];
  end = omp_get_wtime();
  tSerial[1] = end - start;
  printf("Processamento 2 - %f\n", tSerial[1]);
  fflush( stdout );

  // Processamento 3
  start = omp_get_wtime();
  for (i = 0; i < nSize; i++){
    sumX += x[i];
    sumY += y[i];
  }
  end = omp_get_wtime();
  tSerial[2] = end - start;
  printf("Processamento 3 - %f\n", tSerial[2]);

  //Saida de resultados
  printf("-> %f \t %f \t Is Ok?\n", sumX, sumY);

  free(x);
  free(y);

  return 0;
}
