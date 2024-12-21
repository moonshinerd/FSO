#include <iostream>
#include <vector>
#include <queue>

int main() {
    int entrada; // número de processos
    int quantum; // janela de tempo em milissegundos
    std::cin >> entrada >> quantum;

    std::vector<int> pids(entrada); // vetor de PIDs
    std::vector<int> tempo_restante(entrada); // vetor para controlar o tempo restante
    std::queue<int> fila_processos; // fila de processos

    for (int i = 0; i < entrada; i++) {
        int tempo_exec;
        std::cin >> pids[i] >> tempo_exec;
        tempo_restante[i] = tempo_exec * 1000; // converte o tempo de segundos para milissegundos
        fila_processos.push(i); // adiciona o processo na fila
    }

    int tempo_atual = 0; // tempo total passado

    while (!fila_processos.empty()) {
        int i = fila_processos.front();
        fila_processos.pop();

        if (tempo_restante[i] > 0) { // apenas processos com tempo restante
            int tempo_exec = (tempo_restante[i] <= quantum) ? tempo_restante[i] : quantum;
            tempo_atual += tempo_exec;
            tempo_restante[i] -= tempo_exec;

            if (tempo_restante[i] <= 0) {
                // Processo finalizado
                std::cout << pids[i] << " (" << tempo_atual << ")\n";
            } else {
                // Reinsere o processo na fila se ainda não terminou
                fila_processos.push(i);
            }
        }
    }

    return 0;
}
