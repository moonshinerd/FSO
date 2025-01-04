#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


// estrutura necessária para passar argumentos para a função que a thread vai executar
typedef struct {
    int numero_qualquer;
} routine_args;

void* routine(void* args) {
    routine_args* actual_args = (routine_args*) args; // fazendo cast do ponteiro void para o tipo da estrutura
    int numero_qualquer = actual_args->numero_qualquer; // acessando o campo da estrutura
    printf("Teste das threads. O numero de entrada foi: %d. Um beijo.\n\n", numero_qualquer); // printando o valor
    sleep(1); // fazendo a thread dormir por 1 segundo
    printf("A thread %d terminou. Um beijo.\n", numero_qualquer); // printando que a thread terminou
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    routine_args args_t1, args_t2; // criando a estrutura para passar os argumentos da função
    args_t1.numero_qualquer = 42; // atribuindo um valor para o campo da estrutura
    args_t2.numero_qualquer = 21; // atribuindo um valor para o campo da estrutura

    // o pthread create cria uma thread e executa a função routine
    // os argumento que pthread_create recebe são: a thread, atributos da thread, a função que a thread vai executar e os argumentos da função
    // caso a função não receba argumentos, o argumento passado é NULL
    // a função pthread_create retorna 0 se a thread foi criada com sucesso e um valor diferente de 0 caso contrário
    if (pthread_create(&t1, NULL, &routine, (void*)&args_t1) != 0) {
        printf("Erro ao criar a thread 1\n");
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, (void*)&args_t2)) {
        printf("Erro ao criar a thread 2\n");
        return 2;
    }
    // o pthread_join faz com que a thread principal espere a thread t1 terminar
    // os argumentos que pthread_join recebe são: a thread que a thread principal vai esperar e o valor de retorno da thread
    // nesse caso nao nos importamos com o valor de retorno, então passamos NULL
    // sem o pthread_join, a thread principal pode terminar antes das threads t1 e t2 ocasionando no término das threads 
    // assim como a função pthread_create, a função pthread_join retorna 0 se a thread foi finalizada com sucesso e um valor diferente de 0 caso contrário
    if (pthread_join(t1, NULL) != 0) {
        printf("Erro ao esperar a thread 1\n");
        return 3;
    }
    if (pthread_join(t2, NULL) != 0) {
        printf("Erro ao esperar a thread 2\n");
        return 4;
    }
    return 0;
}