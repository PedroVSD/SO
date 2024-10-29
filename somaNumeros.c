#include <stdio.h>
#include <omp.h>
#include <immintrin.h>

void encontrarCombinacoes(int n) {
    FILE *arquivo = fopen("combinacoes.txt", "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    int num_threads = 4;

    // Paraleliza o loop externo com OpenMP
    #pragma omp parallel for num_threads(num_threads) schedule(dynamic)
    for (int x = 1; x <= n / 3; x++) {
        for (int y = x; y <= (n - x) / 2; y++) {
            int alvo = n - x - y; // Calcula o valor de z diretamente

            // Verifica se z é uma combinação válida
            if (alvo >= y) {
                // Usa uma seção crítica para evitar conflito de escrita
                #pragma omp critical
                fprintf(arquivo, "%d + %d + %d = %d\n", x, y, alvo, n);
            }
        }
    }

    fclose(arquivo); // Fecha o arquivo
}

int main() {
    int numero;
    printf("Digite um número: ");
    if (scanf("%d", &numero) != 1) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    //printf("Escrevendo combinações no arquivo combinacoes.txt...\n");
    encontrarCombinacoes(numero);

    //printf("Combinações salvas com sucesso em combinacoes.txt\n");
    return 0;
}
