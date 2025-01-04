#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutex;

// Diferentemente do lock tradicional, o trylock não bloqueia a thread caso o mutex já esteja travado. 
// Em vez disso, ele retorna um valor diferente de 0 para indicar que o mutex está ocupado. 
// Isso é útil para evitar que outras threads fiquem esperando o mutex ser liberado, o que pode ser vantajoso 
// em situações onde não é crítico que a área crítica seja acessada a cada execução da thread. 
// Ou seja, a execução da área crítica pode ser opcional dependendo do estado do mutex.

// Lock tradicional: Se a thread tentar adquirir um mutex já travado, ela fica bloqueada (aguardando) até que o mutex seja liberado.
// Trylock: Verifica se o mutex está disponível sem bloquear a thread. Caso esteja ocupado, a thread pode seguir com outras tarefas ou tomar decisões diferentes.

void* routine(void* args){
    if (pthread_mutex_trylock(&mutex) /* retorna 0 se o mutex foi travado com sucesso e um valor diferente de 0 caso contrário */ == 0){
        printf("Locked\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    } else {
        printf("Didn't get lock\n"); 
    }
    
}

int main(){
    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 4; i++){
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0){
            printf("Erro ao criar a thread %d\n", i);
        }
    }
    for (int i = 0; i < 4; i++){
        if(pthread_join(th[i], NULL) != 0){
            printf("Erro ao esperar a thread %d\n", i);
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}