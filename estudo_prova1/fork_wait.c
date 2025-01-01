#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // executa 
#include <time.h>

// codigo para estudo de fork e wait
// para entender como funciona a funcao fork e wait
int main(int argc, char *argv[]){
    int id = fork(); // essa função cria um processo filho que é uma copia do processo pai e retorna o id do processo filho, no processo pai o id é o id do processo filho, no processo filho o id é 0

    // exemplo de execução de um programa
    int n;
    if (id == 0){
        n = 1;
    } else {
        n = 6;
    }

    wait(); // essa função faz o processo pai esperar o processo filho terminar sua execução
    // sem o wait os processos podem executar ao mesmo tempo e o resultado pode ser imprevisivel
    // um exemplo é o abaixo que sem o wait pode imprimir tanto o caso 1 quanto o caso 2 e variações desses
    //caso 1: 
    //  6 7 8 9 10
    //  1 2 3 4 5
    //caso 2:
    // 6 1 7 2 8 3 9 4 10 5
    //
    // com o wait o resultado sempre será o a seguir, onde o processo filho executa primeiro e o processo pai espera ele terminar:
    // 1 2 3 4 5 6 7 8 9 10
    int i;
    for (i = n; i < n + 5; i++){
        printf("%d ", i);
        fflush(stdout); // faz o buffer ser impresso na tela em tempo real
    }
    if (id == 0){
        printf("\n");
    }

    return 0;
}