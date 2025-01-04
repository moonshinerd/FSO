#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>

/*
Esse código serve para explicar o que é o type pthread_t
pthread_t é um tipo de dado que é utilizado para identificar uma thread
ele vem da biblioteca pthread.h
ele é um tipo de dado que é um inteiro sem sinal
ele é um tipo de dado que é um ponteiro para uma estrutura que contém informações sobre a thread

*/

#define THREAD_NUM 2

void* routine(void* args) {
    pthread_t th = pthread_self(); // essa função retorna o id da thread que a chama
    printf("%ul\n", th); // printa o id da thread
    printf("%d\n", (pid_t) syscall(SYS_gettid)); // essa função retorna o id da thread que a chama
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            printf("Failed to create thread");
        }
        // printf("%ul\n", th[i]);
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Failed to join thread");
        }
    }
    return 0;
}