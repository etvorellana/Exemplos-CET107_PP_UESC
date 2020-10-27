#include <stdio.h>
#include <stdlib.h>

//Compilação Condicional
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
  #define omp_get_num_threads() 1 
#endif

/* Como compilar

gcc -o integralSeq -Wall -O3 integralSeq.c

*/

double f (double x);

int main(){

    double start = omp_get_wtime();

    double integral, a= 0.0, b= 1.0, x, h;
    int n = 4096;
    //int n = 2048;

    h = (b - a)/n;
    integral = (f(a) + f(b))/2;
    x = a;
    for(int i = 1; i < n ; i++){
        x += h;
        integral += f(x);
    } 
    integral *= h;

    printf("Estimativa com %d trapezios\n", n);
    printf("Integral = %.6lf\n", integral);
    double stop = omp_get_wtime();
    printf("Tempo total: %.6lf\n", stop -start);
    return 0;
}

double f(double x){
    return x*x + 1.0;
}