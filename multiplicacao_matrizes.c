#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 250

// Função para multiplicar matrizes
void multiplicarMatrizes(int matA[TAM][TAM], int matB[TAM][TAM], int matC[TAM][TAM]) {
    int i, j, k;
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            matC[i][j] = 0;
            for (k = 0; k < TAM; k++) {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

int main() {
    int matA[TAM][TAM], matB[TAM][TAM], matC[TAM][TAM];
    int i, j;

    // Inicializar matrizes com valores aleatórios
    srand(time(NULL));
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }

    // Medir tempo de execução
    clock_t inicio = clock();
    multiplicarMatrizes(matA, matB, matC);
    clock_t fim = clock();

    // Imprimir tempo de execução
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.6f segundos\n", tempo);

    return 0;
}