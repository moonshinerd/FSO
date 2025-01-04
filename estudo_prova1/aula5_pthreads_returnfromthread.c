#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

// Função executada pela thread
void* roll_dice(){
    int value = (rand() % 6) + 1; // Gera um valor aleatório entre 1 e 6
    int *result = malloc(sizeof(int)); // Aloca memória para armazenar o valor do dado
    *result = value; // Armazena o valor do dado na memória alocada
    printf("Thread Result: %p\n", result); // Imprime o endereço da memória alocada
    return (void*) result; // Retorna o endereço da memória alocada para a thread principal o valor de retorno da thread é passado por referência utilizando void** e armazenado em res
}

int main(){
    int *res;
    pthread_t th;
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual

    // Cria uma nova thread que executa a função roll_dice
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0){
        return 1; 
    }

    // Aguarda a thread terminar e obtém o valor de retorno
    if(pthread_join(th, (void**) &res) != 0){ // O valor de retorno da thread é passado por referência utilizando void** e armazenado em res
        return 2;
    }

    printf("Main Result: %p\n", res); // Imprime o endereço da memória alocada retornado pela thread
    printf("Valor do dado na thread principal: %d\n", *res); // Imprime o valor do dado armazenado na memória alocada
    free(res); // Libera a memória alocada para o valor de retorno da thread
    return 0;
}