#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "queue.h"
#include "thread_routines.h"

int main()
{
    pthread_t producer_thread_ids[MAX_PRODUCER_THREADS];
    pthread_t consumer_thread_ids[MAX_CONSUMER_THREADS];
    shared_queue = initialize_queue(QUEUE_SIZE);


    for (int i = 0; i < MAX_PRODUCER_THREADS; i++) {
        pthread_create(&producer_thread_ids[i], NULL, enqueue_item, rand() % 100);
    }

    display_contents(shared_queue);

    for (int i = 0; i < MAX_CONSUMER_THREADS; i++) {
        pthread_create(&consumer_thread_ids[i], NULL, dequeue_item, NULL);
    }

    display_contents(shared_queue);

    for (int i = 0; i < MAX_PRODUCER_THREADS; i++) {
        pthread_join(producer_thread_ids[i], NULL);
    }

    display_contents(shared_queue);

    for (int i = 0; i < MAX_CONSUMER_THREADS; i++) {
        pthread_join(consumer_thread_ids[i], NULL);
    }

    display_contents(shared_queue);

    display_contents(shared_queue);

    destruct_queue(shared_queue);
    return 0;
}
