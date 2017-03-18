#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "queue.h"
#include "thread_routines.h"
#include "daemon.h"

int main()
{
    make_daemon();

    pthread_t producer_thread_ids[MAX_PRODUCER_THREADS];
    pthread_t consumer_thread_ids[MAX_CONSUMER_THREADS];

    /* 100 integers. We will calculate fibonacci number of these integers. */
    int shared_data[100] = {13, 97, 98, 15, 12, 43, 87, 8, 98, 70, 79, 82, 36,
                            83, 73, 58, 6, 57, 79, 23, 5, 90, 70, 66, 72, 18,
                            97, 8, 31, 22, 46, 4, 23, 33, 72, 65, 10, 50, 10,
                            41, 33, 96, 38, 24, 22, 89, 8, 34, 87, 13, 54, 5,
                            15, 87, 35, 79, 47, 44, 12, 5, 96, 84, 50, 47, 54,
                            5, 53, 15, 8, 65, 48, 61, 69, 78, 82, 27, 78, 71, 2,
                            90, 82, 87, 57, 54, 86, 42, 62, 60, 54, 48, 75, 45,
                            9, 16, 56, 84, 31, 26, 75, 87};

    shared_queue = initialize_queue(QUEUE_SIZE);

    /* Creating producer threads to insert elements from shared_data into
       the queue. */
    for (int i = 0; i < MAX_PRODUCER_THREADS; i++) {
        pthread_create(&producer_thread_ids[i], NULL, enqueue_item, shared_data[i]);
    }

    /* Creating consumer threads to process elements from queue */
    for (int i = 0; i < MAX_CONSUMER_THREADS; i++) {
        pthread_create(&consumer_thread_ids[i], NULL, dequeue_item, NULL);
    }

    /* Waiting for all producer threads to complete */
    for (int i = 0; i < MAX_PRODUCER_THREADS; i++) {
        pthread_join(producer_thread_ids[i], NULL);
    }

    /* Waiting for all consumer threads to complete */
    for (int i = 0; i < MAX_CONSUMER_THREADS; i++) {
        pthread_join(consumer_thread_ids[i], NULL);
    }

    destruct_queue(shared_queue);
    return 0;
}
