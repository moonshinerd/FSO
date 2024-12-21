#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

void calcular_tempo_execucao(struct timeval inicio, struct timeval fim, double *tempo_execucao) {
    *tempo_execucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;
}

int main() {
    char path[256], arg[256];
    double tempo_total = 0.0;

    while (scanf("%255s %255s", path, arg) != EOF) {
        struct timeval inicio, fim;
        gettimeofday(&inicio, NULL);

        pid_t pid = fork();

        if (pid == 0) {
            execl(path, path, arg, (char *)NULL);
            exit(127);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            gettimeofday(&fim, NULL);

            double tempo_execucao;
            calcular_tempo_execucao(inicio, fim, &tempo_execucao);
            tempo_execucao = (double)((int)(tempo_execucao * 10 + 0.5)) / 10.0;
            tempo_total += tempo_execucao;

            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                if (exit_code == 127) {
                    printf("> Erro: No such file or directory\n");
                }
                printf("> Demorou %.1f segundos, retornou %d\n", tempo_execucao, (exit_code == 127) ? 2 : exit_code);
            } else {
                printf("> Demorou %.1f segundos, retornou -1\n", tempo_execucao);
            }
            fflush(stdout);
        } else {
            perror("Erro ao criar processo filho");
            return 1;
        }
    }

    tempo_total = (double)((int)(tempo_total * 10 + 0.5)) / 10.0; // Arredondar tempo total
    printf(">> O tempo total foi de %.1f segundos\n", tempo_total);
    return 0;
}
