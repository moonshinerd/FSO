#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;

void* routine(){
    for(int i = 0; i < 1000000; i++){ // quando as threads executarem teremos uma race condition que vai fazer com que o valor de mails seja diferente de 2000000 pois as threads vão tentar acessar a variável mails ao mesmo tempo então quando uma thread acessar a variável mails a outra thread pode estar acessando a mesma variável e alterando o valor dela o que ja vai estar desatualizado porque ja vai ter sido alterado pela outra thread
    // então basicamente a p1 vai ler um valor de mails, a p2 vai ler o mesmo valor de mails, a p1 vai incrementar o valor de mails e a p2 vai incrementar o valor de mails, então o valor de mails vai ser incrementado duas vezes mas deveria ser incrementado uma vez e diversas variações desse caso
    // p1 pode ler passar para p2 e p2 ler e incrementar 7 vezes quando voltar para p1 ele vai incrementar a partir de onde ele parou sua leitura que será 7 incrementos atrás pois ele já leu o valor de mails antes de p2 incrementar
    // isso nao acontece pra valores pequenos de i porque a execução é muito rápida e a chance de uma thread ler o valor de mails antes da outra é muito pequena
        mails++;
    }
    
}

int main(){
    pthread_t p1, p2;
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
    printf("Número de mails: %d\n", mails);
    return 0;
}