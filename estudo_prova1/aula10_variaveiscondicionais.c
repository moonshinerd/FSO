#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexfuel;
pthread_cond_t condfuel; // uma variavel condicional serve para que uma thread possa esperar por uma condição para executar, ela é usada em conjunto com um mutex. Ela pode ser utilizada no pthread_cond_wait, pthread_cond_signal e pthread_cond_broadcast
//pthread_cond_wait: faz a thread esperar até que a variável condicional seja sinalizada
//pthread_cond_signal: sinaliza a variável condicional para que uma thread que esteja esperando possa continuar a execução
//pthread_cond_broadcast: sinaliza a variável condicional para que todas as threads que estejam esperando possam continuar a execução
int fuel = 0;

void* fuel_filling(void* args){
    for (int i = 0 ; i < 5; i++){
        pthread_mutex_lock(&mutexfuel);
        fuel += 15;
        printf("Filling fuel ... %d\n", fuel);
        pthread_mutex_unlock(&mutexfuel);
        // pthread_cond_signal(&condfuel); // sinaliza a variável condicional para que a thread que esteja esperando possa continuar de onde parou no pthread_cond_wait
        // as entradas no pthread_cond_wait são a variavel condicional já no pthread_cond_signal é a variavel condicional e o mutex

        pthread_cond_broadcast(&condfuel); // sinaliza a variável condicional para que todas as threads que estejam esperando possam continuar de onde pararam no pthread_cond_wait, diferente do pthread_cond_signal que só sinaliza uma thread
        sleep(1);
    }
}

void* car(void* args){
    pthread_mutex_lock(&mutexfuel);
    while (fuel < 40) {
        printf("No fuel. Waiting for fuel ... %d\n", fuel);
        pthread_cond_wait(&condfuel, &mutexfuel); // a thread vai esperar até que a variável condicional seja sinalizada. ou seja ele volta a executar quando o pthread_cond_signal for chamado na função fuel_filling
        // equivalente a:
        // pthread_mutex_unlock(&mutexfuel);
        // espera pelo sinal em condfuel
        // pthread_mutex_lock(&mutexfuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexfuel);
    
}

int main(){
    pthread_t th[2];
    pthread_mutex_init(&mutexfuel, NULL);
    pthread_cond_init(&condfuel, NULL); // a variavel precisa ser inicializada para que possa ser usada
    for (int i = 0; i < 2; i++){
        if(i==1){
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0){
                printf("Erro ao criar a thread %d\n", i);
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0){
                printf("Erro ao criar a thread %d\n", i);
            }
        }
    }

    for (int i = 0; i < 2; i++){
        if(pthread_join(th[i], NULL) != 0){
            printf("Erro ao esperar a thread %d\n", i);
        }
    }
    pthread_mutex_destroy(&mutexfuel);
    pthread_cond_destroy(&condfuel); // a variavel precisa ser destruida para liberar a memória alocada
    return 0;
}