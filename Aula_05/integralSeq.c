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
double int_f(double a, double b);

int main(int argc, char * argv[]){

  double start = omp_get_wtime();
  int n = 1024;
  double integral=0.0, a= 0.0, b= 1.0, x, h;


  if(argc > 1)
		n = atoi(argv[1]);
  if(argc > 2)
		a = atof(argv[2]);
	if(argc > 3)
		b = atof(argv[3]);
	
  h = (b - a)/n;
  
  x = a;
  for(int i = 1; i < n ; i++){
    x += h;
    integral += f(x);
  } 
    
  integral += (f(a) + f(b))/2;
  integral *= h;
  double integral_fab = int_f(a, b);
  double errAbs = abs(integral_fab - integral);
  double errRel = errAbs/abs(integral_fab)*100.0;
  printf(" A integral da função f(x)=x²+1 no \n");
  printf("intervalo de %.2lf a %.2lf pode ser\n", a, b);
  printf("calculada como:\n");
  printf("   3    |%.2lf\n", b);
  printf("  x     |     \n");
  printf(" --- + x|        = %.8lf\n", integral_fab);
  printf("  1     |     \n");
  printf("        |%.2lf\n", a);
  printf(" A integral também pode ser estimada\n");
  printf("utilizando o método dos trapezios. \n");
  printf("A estimativa utilizando %d trapezios\n", n);
  printf("Integral = %.8lf\n", integral);
  printf("Erro absoluto: %.10lf\n", errAbs);
  printf("Erro relativo: %.2lf%%\n", errRel);
  double stop = omp_get_wtime();
  printf("Tempo total: %.6lf\n", stop -start);
  return 0;
}

double f(double x){
  return x*x + 1.0;
}

double int_f(double a, double b){
  double res = (b*b*b)/3 + b;
  res -= ((a*a*a)/3 + a);
  return res;
}