#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* func(void* arg) {
    printf("Inside the child thread execution pool.\n");
    pthread_exit(NULL); // Terminate calling thread explicitly
}
int main() {
    pthread_t ptid;

    // Create a new thread
    if (pthread_create(&ptid, NULL, &func, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    printf("Line printed from main workflow thread context.\n");

    // Check equality
    if (pthread_equal(ptid, pthread_self())) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    // Await child routine thread completion
    pthread_join(ptid, NULL);
    printf("Line printed after child thread successfully ends.\n");

    return 0;
}
