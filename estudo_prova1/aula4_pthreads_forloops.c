#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex; 

void* routine(){
    for(int i = 0; i < 1000000; i++){ 
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex); 
    }
    
}

int main(){
    pthread_t th[4]; // aloca 4 threads em um vetor
    int i;
    pthread_mutex_init(&mutex, NULL); 
    // voce nao deve criar um for loop como no código comentado aqui a baixo pois o pthread_create cria a thread e a executa, então se voce criar um for loop como no código comentado aqui a baixo voce vai criar as threads e esperar elas terminarem antes de criar a próxima thread, o que não é o objetivo
    // for (i == 0; i < 4; i++){
    //     if (pthread_create(&th[i], NULL, &routine, NULL) != 0){
    //         printf("Erro ao criar a thread %d\n", i);
    //         return 1; 
    //     }
    //     if(pthread_join(th[i], NULL) != 0){
    //         printf("Erro ao esperar a thread %d\n", i);
    //         return 2;
    //     }
    //     printf("Thread %d terminou\n", i);
    // }

    // o correto é criar as threads e esperar elas terminarem depois como no codigo abaixo pois assim as threads vão executar ao mesmo tempo
    // então conclui-se que a forma de criar for loops para threads devem ser feitas com cuidado e em for loops separados
    for (i = 0; i < 4; i++){
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0){
            printf("Erro ao criar a thread %d\n", i);
            return 1; 
        }
    }
    for (i = 0; i < 4; i++){
        if(pthread_join(th[i], NULL) != 0){
            printf("Erro ao esperar a thread %d\n", i);
            return 2;
        }
        printf("Thread %d terminou\n", i);
    }

    pthread_mutex_destroy(&mutex); 
    printf("Número de mails: %d\n", mails);
    return 0;
}