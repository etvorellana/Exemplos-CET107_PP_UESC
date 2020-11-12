/* 
 * File:   main.c
 * Author: evalero
 *
 * Created on 28 de Agosto de 2013, 08:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>


double function_1x(double x);

int main(int argc, char *argv[]) {
    double soma = 0, errLim = 0.000000000001l, err = 0;
    int qTrap = 2, i, j, qItera = 1;
    double x_0 = 0.0L, x_N = 100.0L, x, dx;
    double subInt, numInt, numInt_, realInt;
    double start, end, tInicial, tSerial, tParalelo;

    realInt = (x_N * x_N * x_N* x_N) + (x_N * x_N * x_N)  + (x_N * x_N);
    realInt -= (x_N * x_N * x_N) * cos(x_N);
    realInt += 3*(x_N * x_N)*sin(x_N);
    realInt += 6*x_N*cos(x_N);
    realInt += 6*(1-sin(x_N));
    //realInt /= 100000;

    start = omp_get_wtime();
    dx = (x_N - x_0) / qTrap;
    x = x_0;

    subInt = (function_1x(x_0) + function_1x(x_N)) * 0.5;

    for (i = 1; i < qTrap; i++) {
        x += dx;
        soma = soma + function_1x(x);
    }

    numInt = (subInt + soma) * dx;

    printf("Integração Numérica\n");
    printf("Integral = %lf \n", realInt);
    printf("Iteração %3d - ", qItera);
    printf("Trapecios = %8d - ", qTrap);
    printf("Integral = %lf - ", numInt);
    printf("Erro inicial - %.16lf \n", fabs(realInt - numInt) / realInt);

    do {
        x = x_0 - dx * 0.5;
        numInt_ = numInt;
        qItera++;

        for (i = 1; i <= qTrap; i++) {
            x += dx;
            soma = soma + function_1x(x);
        }

        qTrap *= 2;
        dx = (x_N - x_0) / qTrap;

        numInt = (subInt + soma) * dx;
        err = fabs(numInt_ - numInt) / numInt_;
        printf("Iteração %3d - ", qItera);
        printf("Trapecios = %8d - ", qTrap);
        printf("Integral = %lf - ", numInt);
        printf("Erro  - %.16lf \n", err);

    }    while (err > errLim);

    printf("Erro final - %.16lf \n", fabs(realInt - numInt) / realInt);
    
    end = omp_get_wtime();
    tInicial = end - start;
    printf("- Tempo Inicial: ____________________________ %lf \n", tInicial);
    
    printf("Executando a integração para um número fixo de trapecios:\n");
    
    
    start = omp_get_wtime();
    
    dx = (x_N - x_0) / qTrap;
    x = x_0;
    soma = 0;

    subInt = (function_1x(x_0) + function_1x(x_N)) * 0.5;

    for (i = 1; i < qTrap; i++) {
        x += dx;
        soma = soma + function_1x(x);
    }
    
    numInt = (subInt + soma) * dx;
    end = omp_get_wtime();
    tSerial = end - start;  
    
    printf("Integração Numérica\n");
    printf("Integral = %lf \n", realInt);
    printf("Trapecios = %8d - ", qTrap);
    printf("Integral = %lf\n", numInt);
    printf(" * Erro absoluto - %.16lf \n", fabs(realInt - numInt));
    printf(" * Erro relativo - %.16lf \n", fabs(realInt - numInt) / realInt);
    printf("- Tempo Serial: ____________________________ %lf \n", tSerial);
    
    printf("Executando a integração para um número fixo de trapecios com 2:\n");
    
    
    start = omp_get_wtime();
    
    dx = (x_N - x_0) / qTrap;
    x = x_0;
    soma = 0;

    subInt = (function_1x(x_0) + function_1x(x_N)) * 0.5;
    
    #pragma omp parallel for reduction(+:soma)
    for (i = 1; i < qTrap; i++) {
        x = i*dx;
        soma = soma + function_1x(x);
    }
   

    numInt = (subInt + soma) * dx;
    end = omp_get_wtime();
    tParalelo = end - start;  
    
    printf("Integração Numérica\n");
    printf("Integral = %lf \n", realInt);
    printf("Trapecios = %8d - ", qTrap);
    printf("Integral = %lf\n", numInt);
    printf(" * Erro absoluto - %.16lf \n", fabs(realInt - numInt));
    printf(" * Erro relativo - %.16lf \n", fabs(realInt - numInt) / realInt);
    printf("- Tempo Paralelo: ____________________________ %lf \n", tParalelo);
    printf("- speedup: ____________________________ %lf\n", tSerial / tParalelo);
    
    printf("Executando a integração para um número fixo de trapecios com 3:\n");
    
    
    start = omp_get_wtime();
    
    dx = (x_N - x_0) / qTrap;
    x = x_0;
    soma = 0;

    subInt = (function_1x(x_0) + function_1x(x_N)) * 0.5;
    
    #pragma omp parallel for reduction(+:soma) num_threads(3)
    for (i = 1; i < qTrap; i++) {
        x = i*dx;
        soma = soma + function_1x(x);
    }
   

    numInt = (subInt + soma) * dx;
    end = omp_get_wtime();
    tParalelo = end - start;  
    
    printf("Integração Numérica\n");
    printf("Integral = %lf \n", realInt);
    printf("Trapecios = %8d - ", qTrap);
    printf("Integral = %lf\n", numInt);
    printf(" * Erro absoluto - %.16lf \n", fabs(realInt - numInt));
    printf(" * Erro relativo - %.16lf \n", fabs(realInt - numInt) / realInt);
    printf("- Tempo Paralelo: ____________________________ %lf \n", tParalelo);
    printf("- speedup: ____________________________ %lf\n", tSerial / tParalelo);
    
    printf("Executando a integração para um número fixo de trapecios com 4:\n");
    
    
    start = omp_get_wtime();
    
    dx = (x_N - x_0) / qTrap;
    x = x_0;
    soma = 0;

    subInt = (function_1x(x_0) + function_1x(x_N)) * 0.5;
    
    #pragma omp parallel for reduction(+:soma) num_threads(4)
    for (i = 1; i < qTrap; i++) {
        x = i*dx;
        soma = soma + function_1x(x);
    }
   

    numInt = (subInt + soma) * dx;
    end = omp_get_wtime();
    tParalelo = end - start;  
    
    printf("Integração Numérica\n");
    printf("Integral = %lf \n", realInt);
    printf("Trapecios = %8d - ", qTrap);
    printf("Integral = %lf\n", numInt);
    printf(" * Erro absoluto - %.16lf \n", fabs(realInt - numInt));
    printf(" * Erro relativo - %.16lf \n", fabs(realInt - numInt) / realInt);
    printf("- Tempo Paralelo: ____________________________ %lf \n", tParalelo);
    printf("- speedup: ____________________________ %lf\n", tSerial / tParalelo);

    return 0;

}

double function_1x(double x) {
    return ((4 + sin(x))*(x * x * x) + 3*(x * x) + 2 * x);
}




