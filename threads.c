#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Função que será executada pela primeira thread (imprime números)
void* print_numbers(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Número: %d\n", i);
        sleep(1);  // Pausa de 1 segundo
    }
    return NULL;
}

// Função que será executada pela segunda thread (imprime letras)
void* print_letters(void* arg) {
    for (char letter = 'A'; letter <= 'E'; letter++) {
        printf("Letra: %c\n", letter);
        sleep(1);  // Pausa de 1 segundo
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Criação das duas threads
    if (pthread_create(&thread1, NULL, print_numbers, NULL)) {
        fprintf(stderr, "Erro ao criar a thread1\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, print_letters, NULL)) {
        fprintf(stderr, "Erro ao criar a thread2\n");
        return 1;
    }

    // Aguarda o término das duas threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Execução das threads finalizada.\n");
    return 0;
}
