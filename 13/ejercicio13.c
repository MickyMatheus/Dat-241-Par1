#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define N 6
#define TAM 100 

int main(int argc, char *argv[]) {
    int rank, size;
    char vector[N][TAM] = {
        "cadena0", "cadena1", "cadena2", "cadena3", "cadena4", "cadena5"
    };

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        if (rank == 0) {
            printf("Este programa requiere exactamente 3 procesadores.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("Procesador 0: Enviando el vector de cadenas\n");
        MPI_Send(vector, N * TAM, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vector, N * TAM, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
    }

    if (rank == 1) {
        char vector_local[N][TAM];
        MPI_Recv(vector_local, N * TAM, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Procesador 1: Desplegando posiciones pares:\n");
        for (int i = 0; i < N; i += 2) {
            printf("Posicion %d: %s\n", i, vector_local[i]);
        }
    }

    if (rank == 2) {
        char vector_local[N][TAM];
        MPI_Recv(vector_local, N * TAM, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Procesador 2: Desplegando posiciones impares:\n");
        for (int i = 1; i < N; i += 2) {
            printf("Posicion %d: %s\n", i, vector_local[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
