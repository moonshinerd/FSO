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
            // Processo filho executa apenas o comando
            execl(path, path, arg, (char *)NULL);

            // Se execl falhar, imprime erro e encerra
            fprintf(stderr, "> Erro: %s\n", strerror(errno));
            exit(127); // Código padrão para comando não encontrado
        } else if (pid > 0) {
            // Processo pai
            int status;
            waitpid(pid, &status, 0);
            gettimeofday(&fim, NULL);

            double tempo_execucao;
            calcular_tempo_execucao(inicio, fim, &tempo_execucao);
            tempo_execucao = (double)((int)(tempo_execucao * 10 + 0.5)) / 10.0; // Arredondar para 1 decimal
            tempo_total += tempo_execucao;

            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                if (exit_code == 127) {
                    // Erro de execução do comando
                    printf("> Erro: No such file or directory\n");
                    printf("> Demorou 0.0 segundos, retornou 2\n");
                } else {
                    // Apenas imprime uma vez o tempo e retorno
                    printf("> Demorou %.1f segundos, retornou %d\n", tempo_execucao, exit_code);
                }
            } else {
                printf("> Demorou %.1f segundos, retornou -1\n", tempo_execucao);
            }
        } else {
            // Erro ao criar processo
            perror("Erro ao criar processo filho");
            return 1;
        }
    }

    // Impressão total no final
    printf(">> O tempo total foi de %.1f segundos\n", tempo_total);
    return 0;
}
