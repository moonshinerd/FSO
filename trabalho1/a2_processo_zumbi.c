#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t zumbi = 0;
int sinais_recebidos = 0;

void trata_sinal(int sig) {
    sinais_recebidos++;

    if (sinais_recebidos == 1) {
        pid_t pid = fork();
        if (pid == 0) {
            exit(0);
        } else if (pid > 0) {
            zumbi = pid;
        }
    } else if (sinais_recebidos == 2) {
        if (zumbi > 0) {
            waitpid(zumbi, NULL, 0);
            zumbi = 0;
        }
    } else if (sinais_recebidos == 3) {
        exit(0);
    }
}

int main() {
    signal(SIGUSR1, trata_sinal);
    signal(SIGUSR2, trata_sinal);

    while (1) {
        pause();
    }

    return 0;
}
