#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Matrizes A, B e C globais
    double A[N][N], B[N][N], C[N][N];

    // Matrizes locais
    double A_local[N/size][N], C_local[N/size][N];

    // Inicializar a matriz B (matriz global)
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                B[i][j] = (double)(j + 1);
            }
        }
    }

    // Distribute the matrix A to all processes
    MPI_Scatter(A, (N*N/size), MPI_DOUBLE, A_local, (N*N/size), MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Broadcast matrix B to all processes (since B is used by all processes)
    MPI_Bcast(B, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Start time for matrix multiplication
    double t0 = MPI_Wtime();  

    // Perform local matrix multiplication
    int linhas_por_processo = N / size;
    for (int i = 0; i < linhas_por_processo; i++) {
        for (int j = 0; j < N; j++) {
            C_local[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                C_local[i][j] += A_local[i][k] * B[k][j];
            }
        }
    }

    // End time for matrix multiplication
    double t1 = MPI_Wtime();

    // Collect the local matrices C_local to the global matrix C
    MPI_Gather(C_local, (N*N/size), MPI_DOUBLE, C, (N*N/size), MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Print the time taken for matrix multiplication
    if (rank == 0) {
        printf("Tempo total de multiplicação: %f segundos\n", t1 - t0);
    }

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
