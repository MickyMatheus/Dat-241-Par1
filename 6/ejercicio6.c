#include <stdio.h>

void fibonacci(int n) {
    int fib[2] = {0, 1};

    printf("Secuencia de Fibonacci:\n");


    if (n >= 1) {
        printf("%d\n", fib[0]);
    }


    if (n >= 2) {
        printf("%d\n", fib[1]);
    }

    for (int i = 3; i <= n; i++) {
        int siguiente = fib[0] + fib[1];

        printf("%d\n", siguiente);

        fib[0] = fib[1];   // El segundo término se convierte en el primero
        fib[1] = siguiente; // El nuevo término se convierte en el segundo
    }
}

int main() {
    int n;
    printf("Ingrese el número de términos de Fibonacci que desea calcular: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Por favor, ingrese un número mayor a 0.\n");
    } else {
        fibonacci(n);
    }

    return 0;
}
