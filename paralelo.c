                          
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4 

void imprimirMatriz(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N];
    int local_A[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != N) {
        if (rank == 0)
            printf("Este programa requer exatamente %d processos.\n", N);
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j + 1;
                B[i][j] = (i == j) ? 1 : 0;
            }
    }

    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, N, MPI_INT, local_A, N, MPI_INT, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();
    int local_C[N];
    for (int j = 0; j < N; j++) {
        local_C[j] = 0;
        for (int k = 0; k < N; k++) {
            local_C[j] += local_A[k] * B[k][j];
        }
    }

    double end_time = MPI_Wtime();
    double local_duration = end_time - start_time;

    MPI_Gather(local_C, N, MPI_INT, C, N, MPI_INT, 0, MPI_COMM_WORLD);
    double max_duration;
    MPI_Reduce(&local_duration, &max_duration, 1, MPI_DOUBLE, MPI_MAX, 0, MPI>
    if (rank == 0) {
        printf("Resultado da multiplicação (MPI):\n");
        imprimirMatriz(C);
        printf("Tempo de execução (paralelo, MPI): %f segundos\n", max_durati>
    }

    MPI_Finalize();
    return 0;
}



