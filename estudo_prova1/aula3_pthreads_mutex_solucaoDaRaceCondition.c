#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex; // é basicamente um semáforo que só uma thread pode acessar por vez
// seria equivalente ao código comentado aqui a baixo só que mais eficiente e já embutido dentro da biblioteca pthread. 
// outra diferença é que o mutex vai funcionar com mais de duas threads ao mesmo tempo diferente do código comentado que só funcionaria com duas threads
// void* routine(){
//     for(int i = 0; i < 1000000; i++){ 
//         if (lock == 1){
//             while(lock == 1){
//                 // espera a outra thread terminar de acessar a variável mails
//             }
//         }
//         lock = 1;
//         mails++;
//         lock = 0;
//     }
    
// }

void* routine(){
    for(int i = 0; i < 1000000; i++){ 
        pthread_mutex_lock(&mutex); // trava o mutex para que nenhuma outra thread possa acessar a variável mails enquanto a thread atual estiver acessando
        mails++;
        pthread_mutex_unlock(&mutex); // destrava o mutex para que outra thread possa acessar a variável mails pois a thread atual já terminou de acessar
    }
    
}

int main(){
    pthread_t p1, p2;
    pthread_mutex_init(&mutex, NULL); // inicializa o mutex para que ele possa ser usado
    if (pthread_create(&p1, NULL, &routine, NULL) != 0){
        return 1; // no caso de erro ao criar a thread
    }
    if (pthread_create(&p2, NULL, &routine, NULL) != 0){
        return 2; // no caso de erro ao criar a thread
    }
    if (pthread_join(p1, NULL) != 0){
        return 3; // no caso de erro ao esperar a thread
    }
    if (pthread_join(p2, NULL) != 0){
        return 4; // no caso de erro ao esperar a thread
    }
    pthread_mutex_destroy(&mutex); // destrói o mutex para liberar a memória alocada
    printf("Número de mails: %d\n", mails);
    return 0;
}