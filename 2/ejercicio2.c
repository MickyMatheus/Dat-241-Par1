#include <stdio.h>


int sumar(int a, int b) {
    return a + b;
}

int restar(int a, int b) {
    return a - b;
}

int multiplicar(int a, int b) {
    return a * b;
}

float dividir(int a, int b) {
    if (b != 0) {
        return (float) a / b;
    } else {
        printf("Error: División por cero no permitida.\n");
        return 0;
    }
}

int main() {
    int num1, num2;
    printf("Ingrese el primer número: ");
    scanf("%d", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%d", &num2);

    // Llamada a las funciones
    printf("Suma: %d\n", sumar(num1, num2));
    printf("Resta: %d\n", restar(num1, num2));
    printf("Multiplicación: %d\n", multiplicar(num1, num2));
    printf("División: %.2f\n", dividir(num1, num2));

    return 0;
}
