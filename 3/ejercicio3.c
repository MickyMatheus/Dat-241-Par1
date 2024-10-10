#include <stdio.h>

void suma(int *a, int *b, int *resultado) {
    *resultado = *a + *b;
}

void resta(int *a, int *b, int *resultado) {
    *resultado = *a - *b;
}

void multiplicacion(int *a, int *b, int *resultado) {
    *resultado = (*a) * (*b);
}

void division(int *a, int *b, float *resultado) {
    if (*b != 0) {
        *resultado = (float) *a / *b;
    } else {
        printf("Error: División por cero.\n");
    }
}

int main() {
    int num1, num2, resultado;
    float resultado_division;
    int opcion;

    printf("Ingresa dos números enteros: ");
    scanf("%d %d", &num1, &num2);

    printf("Elige una operación: \n1. Suma\n2. Resta\n3. Multiplicación\n4. División\n");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            suma(&num1, &num2, &resultado);
            printf("Resultado de la suma: %d\n", resultado);
            break;
        case 2:
            resta(&num1, &num2, &resultado);
            printf("Resultado de la resta: %d\n", resultado);
            break;
        case 3:
            multiplicacion(&num1, &num2, &resultado);
            printf("Resultado de la multiplicación: %d\n", resultado);
            break;
        case 4:
            division(&num1, &num2, &resultado_division);
            if (num2 != 0) {
                printf("Resultado de la división: %.2f\n", resultado_division);
            }
            break;
        default:
            printf("Opción no válida.\n");
    }

    return 0;
}
