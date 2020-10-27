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

gcc -o integralPar_Alt -Wall -fopenmp -O2 integralPar_Alt.c

*/

double f (double x);

int main(){

    double start = omp_get_wtime();

    //double integral, a= 0.0, b= 1.0, x, h;
    double integral, a= 0.0, b= 1.0, h;
    int n = 4096;
    //int n = 2048;

    h = (b - a)/n;
    //integral = (f(a) + f(b))/2;
    //x = a;
    #pragma omp parallel
    {   
        double integral_loc = 0.0;
        #pragma omp for
        for(int i = 1; i < n ; i++){
            //x += h;
            integral_loc += f(a + i*h);
        }
        //#pragma omp single
        //#pragma omp master
        //#pragma omp barrier
        #pragma omp for ordered
        for(int i = 0; i < omp_get_num_threads(); i++){
            #pragma omp ordered
            {
                integral += integral_loc;
            }
        }
    } 
    integral += (f(a) + f(b))/2;
    integral *= h;

    printf("Estimativa com %d trapezios\n", n);
    printf("Integral = %.6lf\n", integral);
    double stop = omp_get_wtime();
    printf("Tempo total: %.6lf\n", stop -start);
    return 0;
}

//Sugestão um polinomio de grau 8
double f(double x){
    return x*x + 1.0;
}