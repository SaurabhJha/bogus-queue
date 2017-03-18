#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "queue.h"
#include "thread_routines.h"
#include "daemon.h"

int main()
{
    /* TODO: Make syslog work and enable it. */
    /*make_daemon();*/

    pthread_t producer_thread_ids[MAX_PRODUCER_THREADS];
    pthread_t consumer_thread_ids[MAX_CONSUMER_THREADS];

    /* 100 integers. We will calculate fibonacci number of these integers. */
    int shared_data[100] = {3, 7, 8, 5, 2, 3, 7, 8, 8, 0, 9, 2, 6, 3, 3, 8, 6,
                            7, 9, 3, 5, 0, 0, 6, 2, 8, 7, 8, 1, 2, 6, 4, 3, 3,
                            2, 5, 0, 0, 0, 1, 3, 6, 8, 4, 2, 9, 8, 4, 7, 3, 4,
                            5, 5, 7, 5, 9, 7, 4, 2, 5, 6, 4, 0, 7, 4, 5, 3, 5,
                            8, 5, 8, 1, 9, 8, 2, 7, 8, 1, 2, 0, 2, 7, 7, 4, 6,
                            2, 2, 0, 4, 8, 5, 5, 9, 6, 6, 4, 1, 6, 5, 7};

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
