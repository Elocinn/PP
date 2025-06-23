#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiplicarMatrizes(int **A, int **B, int **C, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void imprimirMatriz(int **M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N;

    printf("Digite o tamanho da matriz (N): ");
    fflush(stdout);
    scanf("%d", &N);

    int **A = malloc(N * sizeof(int *));
    int **B = malloc(N * sizeof(int *));
    int **C = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j + 1;
            B[i][j] = (i == j) ? 1 : 0; 
        }

    clock_t start = clock();

    multiplicarMatrizes(A, B, C, N);

    clock_t end = clock();
    double tempo_execucao = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Resultado da multiplicação (sequencial):\n");
    imprimirMatriz(C, N);

    printf("Tempo de execução (sequencial): %.6f segundos\n", tempo_execucao);

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    }
    free(A);
    free(B);
    free(C);

    return 0;
}

