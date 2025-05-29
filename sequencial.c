#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4  // tamanho da matriz (NxN)

void multiplicarMatrizes(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void imprimirMatriz(int M[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Inicialização das matrizes
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j + 1;
            B[i][j] = (i == j) ? 1 : 0;  // matriz identidade
        }
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4  // tamanho da matriz (NxN)

void multiplicarMatrizes(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void imprimirMatriz(int M[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Inicialização das matrizes
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j + 1;
            B[i][j] = (i == j) ? 1 : 0;  // matriz identidade
        }
    // Medir tempo de execução
    clock_t start = clock();

    multiplicarMatrizes(A, B, C);

    clock_t end = clock();
    double tempo_execucao = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Resultado da multiplicação (sequencial):\n");
    imprimirMatriz(C);

    printf("Tempo de execução (sequencial): %.6f segundos\n", tempo_execucao);

    return 0;
}

