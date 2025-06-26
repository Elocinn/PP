#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void printMatrix(int *matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", matrix[i * N + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiply(int *A, int *B, int *C, int rows, int N) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

int main(int argc, char **argv) {
    int rank, size, N;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *A = NULL, *B = NULL, *C = NULL;

    if (rank == 0) {
        printf("Digite o tamanho da matriz (N): ");
        fflush(stdout);
        scanf("%d", &N);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_proc = N / size;
    int remainder = N % size;
    int local_rows = rows_per_proc + (rank < remainder ? 1 : 0);
    int offset = rank * rows_per_proc + (rank < remainder ? rank : remainder);

    // Alocação das matrizes locais e da matriz B
    int *local_A = (int *)malloc(local_rows * N * sizeof(int));
    int *local_C = (int *)malloc(local_rows * N * sizeof(int));
    B = (int *)malloc(N * N * sizeof(int));

    if (rank == 0) {
        A = (int *)malloc(N * N * sizeof(int));
        C = (int *)malloc(N * N * sizeof(int));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i * N + j] = i + j + 1;
                B[i * N + j] = (i == j) ? 1 : 0;
            }
        }

        for (int proc = 1; proc < size; proc++) {
            int proc_rows = rows_per_proc + (proc < remainder ? 1 : 0);
            int proc_offset = proc * rows_per_proc + (proc < remainder ? proc : remainder);
            MPI_Send(&A[proc_offset * N], proc_rows * N, MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
        for (int i = 0; i < local_rows * N; i++) {
            local_A[i] = A[i];
        }
    } else {
        MPI_Recv(local_A, local_rows * N, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    double start = MPI_Wtime();
    multiply(local_A, B, local_C, local_rows, N);
    double end = MPI_Wtime();

    if (rank == 0) {
        for (int i = 0; i < local_rows * N; i++) {
            C[i] = local_C[i];
        }

        for (int proc = 1; proc < size; proc++) {
            int proc_rows = rows_per_proc + (proc < remainder ? 1 : 0);
            int proc_offset = proc * rows_per_proc + (proc < remainder ? proc : remainder);
            MPI_Recv(&C[proc_offset * N], proc_rows * N, MPI_INT, proc, 1, MPI_COMM_WORLD, &status);
        }

        printf("Resultado (Matriz C = A x B):\n");
        printMatrix(C, N);
        printf("Tempo total: %.6f segundos\n", end - start);
    } else {
        MPI_Send(local_C, local_rows * N, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    free(local_A);
    free(local_C);
    free(B);
    if (rank == 0) {
        free(A);
        free(C);
    }

    MPI_Finalize();
    return 0;
}
