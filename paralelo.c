                          
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  // tamanho da matriz (NxN)

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

   // Inicialização das matrizes no processo 0
    if (rank == 0) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j + 1;
                B[i][j] = (i == j) ? 1 : 0;
            }
    }

    // Broadcast da matriz B
    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter de linhas da matriz A
    MPI_Scatter(A, N, MPI_INT, local_A, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Tempo de início (depois do Scatter)
    double start_time = MPI_Wtime();

    // Cálculo de uma linha da matriz C
    int local_C[N];
    for (int j = 0; j < N; j++) {
        local_C[j] = 0;
        for (int k = 0; k < N; k++) {
            local_C[j] += local_A[k] * B[k][j];
        }
    }

    double end_time = MPI_Wtime();
    double local_duration = end_time - start_time;

    // Gather das linhas calculadas
    MPI_Gather(local_C, N, MPI_INT, C, N, MPI_INT, 0, MPI_COMM_WORLD);
    // Obter o tempo máximo entre os processos
    double max_duration;
    MPI_Reduce(&local_duration, &max_duration, 1, MPI_DOUBLE, MPI_MAX, 0, MPI>

    // Apenas o processo 0 imprime o resultado
    if (rank == 0) {
        printf("Resultado da multiplicação (MPI):\n");
        imprimirMatriz(C);
        printf("Tempo de execução (paralelo, MPI): %f segundos\n", max_durati>
    }

    MPI_Finalize();
    return 0;
}



