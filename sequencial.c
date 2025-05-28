#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1000

double A[N][N], B[N][N], R[N][N];

int main() {
    // Inicialização das matrizes A e B
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            A[i][j] = (double)(i + 1);
            B[i][j] = (double)(j + 1);
        }
    }

    // Medir o tempo de execução
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Multiplicação de matrizes (algoritmo cúbico)
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            R[i][j] = 0.0;
            for(int k = 0; k < N; k++){
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);

    // Calcular o tempo em segundos
    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
    printf("Tempo sequencial: %f segundos\n", tempo);

    return 0;
}
