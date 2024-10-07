#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

int main() {
    char command[MAX_COMMAND_LENGTH];

    printf("Bem-vindo ao terminal simples em C!\n");
    printf("Digite 'exit' para sair.\n");

    while (1) {
        printf("> "); // Prompt do terminal
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("Erro ao ler o comando.\n");
            continue;
        }

        // Remover o caractere de nova linha do final do comando
        command[strcspn(command, "\n")] = '\0';

        // Verificar se o comando é "exit" para sair do loop
        if (strcmp(command, "exit") == 0) {
            printf("Saindo...\n");
            break;
        }

        // Executar o comando usando a função system()
        int ret = system(command);
        if (ret == -1) {
            printf("Erro ao executar o comando.\n");
        }
    }

    return 0;
}
