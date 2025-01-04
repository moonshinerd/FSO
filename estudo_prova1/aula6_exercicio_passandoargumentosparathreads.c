#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* args){
    int index = *((int*) args);
    printf("%d ", primes[index]);
    free(args);
}

int main(){
    pthread_t th[10];
    for (int i = 0; i < 10; i++){
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, (void*)a) != 0){
            printf("Erro ao criar a thread %d\n", i);
            return 1; 
        }
    }
    for (int i = 0; i < 10; i++){
        if(pthread_join(th[i], NULL) != 0){
            printf("Erro ao esperar a thread %d\n", i);
            return 2;
        }
        
    }
    return 0;
}