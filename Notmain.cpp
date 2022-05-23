#include <pthread.h>
#include <stdio.h>
/* A mutex protecting printf. */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/* Prints x’s . The parameter is unused. Does not return.
*/
void* print_xs(void* unused) {
    while (1) {
        pthread_mutex_lock (&mutex);
        printf("x\n");
        pthread_mutex_unlock (&mutex);
    }
    return NULL;
}
/* The main program. */
int main() {
    pthread_t thread_id;
/* Create a new thread. The new thread will run the
print_xs
function. */
    pthread_create(&thread_id, NULL, &print_xs, NULL);
/* Print o’s continuously */
    while (1) {
        pthread_mutex_lock (&mutex);
        printf("o\n");
        pthread_mutex_unlock (&mutex);
    }
    return 0;
}