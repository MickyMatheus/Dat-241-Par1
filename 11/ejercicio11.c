#include <stdio.h>
#include <mpi.h>

#define N 8  // Tamaño del vector (puede cambiarse)

int main(int argc, char *argv[]) {
    int rank, size;
    int vectorA[N], vectorB[N], resultado[N];
    
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
        printf("Procesador 0: Inicializando vectores\n");
        for (int i = 0; i < N; i++) {
            vectorA[i] = i + 1;
            vectorB[i] = i + 1;
        }

        MPI_Send(vectorA, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vectorB, N, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Send(vectorA, N, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(vectorB, N, MPI_INT, 2, 1, MPI_COMM_WORLD);
    }

    if (rank == 1) {
        MPI_Recv(vectorA, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vectorB, N, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        for (int i = 1; i < N; i += 2) {
            resultado[i] = vectorA[i] + vectorB[i];
        }

        MPI_Send(resultado, N, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    if (rank == 2) {
        MPI_Recv(vectorA, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vectorB, N, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        for (int i = 0; i < N; i += 2) {
            resultado[i] = vectorA[i] + vectorB[i];
        }

        MPI_Send(resultado, N, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        int resultado_impares[N], resultado_pares[N];

        MPI_Recv(resultado_impares, N, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(resultado_pares, N, MPI_INT, 2, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) {
                resultado[i] = resultado_pares[i];
            } else {
                resultado[i] = resultado_impares[i];
            }
        }

        printf("Procesador 0: Resultado de la suma de los vectores:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
