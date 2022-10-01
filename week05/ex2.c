#include <stdio.h>
#include <pthread.h>

#define STRING_SIZE 256
#define N 10

typedef struct {
    pthread_t id;
    int i;
    char message[STRING_SIZE];
} Thread;

void* thread_func(void* th) {
    Thread* thread = (Thread*) th;
    printf("%lu - %s\n", thread->id, thread->message);
    return NULL;
}

int main() {
    Thread threads[N];
    for (int i = 0; i < N; i++) {
        threads[i].i = i;
        sprintf(threads[i].message, "Hello from thread %d", i);
        pthread_create(&threads[i].id, NULL, thread_func, &threads[i]);
        printf("Thread %d is created\n", i);
        pthread_join(threads[i].id, NULL);
    }
}
