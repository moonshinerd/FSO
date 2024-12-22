#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0;
pthread_mutex_t mut;

extern int work(int id);

struct thread_arg {
    int vezes;
};

void *thread_func(void *arg) {
    struct thread_arg *args = (struct thread_arg *)arg;

    for (int i = 0; i < args->vezes; i++) {
        int id;

        pthread_mutex_lock(&mut);
        id = count++;
        pthread_mutex_unlock(&mut);

        work(id);
    }

    return NULL;
}
