#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

double executar_codigo(char *cmd, char *arg) {
    struct timeval inicio, fim;
    double tempo_decorrido = 0.0;
    int status;

    gettimeofday(&inicio, NULL);
    pid_t pid = fork();

    if (pid == 0) {
        execl(cmd, cmd, arg, (char *)NULL);
        printf("> Erro: %s\n", strerror(errno));
        fclose(stdin);
        exit(errno);
    }

    if (waitpid(pid, &status, WUNTRACED))
        gettimeofday(&fim, NULL);

    double segundos = fim.tv_sec - inicio.tv_sec;
    double microssegundos = fim.tv_usec - inicio.tv_usec;
    microssegundos /= 1000000;
    tempo_decorrido = segundos + microssegundos;

    printf("> Demorou %.1lf segundos, retornou %d\n", tempo_decorrido, WEXITSTATUS(status));

    fflush(stdout);
    return tempo_decorrido;
}

int main() {
    char cmd[256];
    char arg[256];
    double tempo_total = 0.0;

    while (scanf("%s %s", cmd, arg) != EOF) {
        tempo_total += executar_codigo(cmd, arg);
    }

    printf(">> O tempo total foi de %.1lf segundos\n", tempo_total);
    return 0;
}
