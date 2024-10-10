#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4

void print_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Matriz A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j;
            }
        }
        print_matrix(A);

        printf("\nMatriz B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                B[i][j] = i * j;
            }
        }
        print_matrix(B);
        printf("\n");
    }

    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_process = N / size;
    int start_row = rank * rows_per_process;
    int end_row = (rank == size - 1) ? N : start_row + rows_per_process;

    int local_A[rows_per_process][N];
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int row_start = i * rows_per_process;
            MPI_Send(&A[row_start][0], rows_per_process * N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        for (int i = 0; i < rows_per_process; i++) {
            for (int j = 0; j < N; j++) {
                local_A[i][j] = A[i][j];
            }
        }
    } else {
        MPI_Recv(&local_A, rows_per_process * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int local_C[rows_per_process][N];
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < N; j++) {
            local_C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                local_C[i][j] += local_A[i][k] * B[k][j];
            }
        }
    }

    if (rank == 0) {
        for (int i = 0; i < rows_per_process; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = local_C[i][j];
            }
        }
        for (int i = 1; i < size; i++) {
            int row_start = i * rows_per_process;
            MPI_Recv(&C[row_start][0], rows_per_process * N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        printf("Matriz Resultante C:\n");
        print_matrix(C);
    } else {
        MPI_Send(&local_C, rows_per_process * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
