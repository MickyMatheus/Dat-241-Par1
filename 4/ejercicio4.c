#include <stdio.h>

void calcularPiIterativo(int iteraciones, double *pi) {
    double sumatoria = 0.0;
    int signo = 1;
    
    for (int i = 0; i < iteraciones; i++) {
        double termino = signo * (1.0 / (2 * i + 1));
        sumatoria += termino;
        
        *pi = 4.0 * sumatoria;
        printf("Iteración %d: Término = %.15f, Sumatoria = %.15f, Pi = %.15f\n", i + 1, termino, sumatoria, *pi);
        
        signo *= -1; 
    }
}

void calcularPiRecursivo(int iteraciones, int actual, double sumatoria, double *pi) {

    if (actual == iteraciones) {
        *pi = 4.0 * sumatoria;
        return;
    }

    double termino = (actual % 2 == 0 ? 1.0 : -1.0) / (2 * actual + 1);
    
    double valorPi = 4.0 * (sumatoria + termino);
    printf("Iteración %d: Término = %.15f, Sumatoria = %.15f, Pi = %.15f\n", actual + 1, termino, sumatoria + termino, valorPi);

    // Llamada recursiva
    calcularPiRecursivo(iteraciones, actual + 1, sumatoria + termino, pi);
}

int main() {
    int iteraciones;
    double pi_iterativa = 0.0;
    double pi_recursiva = 0.0;

    printf("Ingrese el número de iteraciones: ");
    scanf("%d", &iteraciones);

    printf("\nCálculo de Pi de manera iterativa:\n");
    calcularPiIterativo(iteraciones, &pi_iterativa);
    
    printf("\nCálculo de Pi de manera recursiva:\n");
    calcularPiRecursivo(iteraciones, 0, 0.0, &pi_recursiva);

    printf("\nEl valor aproximado de Pi (iterativo) es: %.15f\n", pi_iterativa);
    printf("El valor aproximado de Pi (recursivo) es: %.15f\n", pi_recursiva);

    return 0;
}
