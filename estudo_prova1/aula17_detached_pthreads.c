#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/*
esse codigo serve para explicar o que é uma thread detached(thread desanexada) e como criar uma thread detached
*/

#define THREAD_NUM 2

void* routine(void* args) {
    sleep(1);
    printf("Finished execution\n");
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    pthread_attr_t detachedThread; // declara um atributo para a thread
    pthread_attr_init(&detachedThread); // inicializa o atributo para a thread
    pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED); // declara que essa thread é detached, ou seja, ela não precisa ser esperada para terminar a execução o que basicamente faz com que a thread principal não espere a thread terminar para terminar a execução
    
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], &detachedThread, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
        // pthread_detach(th[i]);
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_attr_destroy(&detachedThread); // destrói o atributo para liberar a memória alocada
    pthread_exit(0);
}