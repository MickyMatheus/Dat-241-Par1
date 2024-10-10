#include <stdio.h>
#include <omp.h>
#include <math.h>

int main() {
    int n = 20; 
    int fib[n];
    double phi = (1 + sqrt(5)) / 2; 

    #pragma omp parallel for shared(fib, n) private(i)
    for (int i = 0; i < n; i++) {
        fib[i] = (int)((pow(phi, i) - pow(1 - phi, i)) / sqrt(5));
    }


    printf("Serie de Fibonacci hasta el término %d:\n", n);
    for (int i = 0; i < n; i++) {
        printf("fib[%d] = %d\n", i, fib[i]);
    }

    return 0;
}
