#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_barrier_t barrier; // uma barreira é um ponto de sincronização onde as threads esperam até que todas as threads tenham chegado nesse ponto para continuar

void* routine(void* args) {
    while (1) {
        printf("Waiting at the barrier...\n");
        sleep(1);
        pthread_barrier_wait(&barrier); // faz a thread esperar até que todas as threads tenham chegado nesse ponto
        printf("We passed the barrier\n");
        sleep(1);
    }
}

int main(int argc, char *argv[]) {
	pthread_t th[10];
	int i;
    pthread_barrier_init(&barrier, NULL, 10); // os argumentos para iniciar são a barreira, os atributos da barreira e o número de threads que devem chegar na barreira para que as threads possam continuar
	for (i = 0; i < 10; i++) {
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
			printf("Failed to create thread");
		}
	}
	for (i = 0; i < 10; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			printf("Failed to join thread");
		}
	}
    pthread_barrier_destroy(&barrier); // destrói a barreira para liberar a memória alocada
	return 0;
}