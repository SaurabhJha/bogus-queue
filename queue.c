#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct queue *initialize_queue(int queue_length)
{
    struct queue *queue_object;

    /* Initialize state variables */
    queue_object = (struct queue *) malloc(sizeof(struct queue));
    queue_object->storage = (int *) malloc(sizeof(int) * queue_length);
    queue_object->length = queue_length;
    queue_object->front = 0;
    queue_object->rear = 0;
    for (int i = 0; i < queue_length; i++) {
        queue_object->storage[i] = SENTINEL;
    }

    /* Initialize synchronization variables */
    queue_object->mutex  = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    queue_object->queue_has_space = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    queue_object->queue_has_element = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    pthread_mutex_init(queue_object->mutex, NULL);
    pthread_cond_init(queue_object->queue_has_space, NULL);
    pthread_cond_init(queue_object->queue_has_element, NULL);

    return queue_object;
}

void destruct_queue(struct queue *queue_object)
{
    /* Destroy synchronization variables */
    pthread_mutex_destroy(queue_object->mutex);
    pthread_cond_destroy(queue_object->queue_has_space);
    pthread_cond_destroy(queue_object->queue_has_element);
    free(queue_object->mutex);
    free(queue_object->queue_has_space);
    free(queue_object->queue_has_element);

    /* Destroy state variables */
    free(queue_object->storage); /* Probably unnecessary. */

    free(queue_object);
}

bool enqueue(struct queue *queue_object, int element)
{
    pthread_mutex_lock(queue_object->mutex);

    while (is_queue_full(queue_object)) {
        pthread_cond_wait(queue_object->queue_has_space, queue_object->mutex);
    }

    queue_object->storage[queue_object->rear] = element;

    if (queue_object->rear == queue_object->length - 1) {
        queue_object->rear = 0;
    } else {
        queue_object->rear += 1;
    }

    pthread_cond_signal(queue_object->queue_has_element);
    pthread_mutex_unlock(queue_object->mutex);

    return true;
}

int dequeue(struct queue *queue_object)
{
    int element;

    pthread_mutex_lock(queue_object->mutex);

    while (is_queue_empty(queue_object)) {
        pthread_cond_wait(queue_object->queue_has_element, queue_object->mutex);
    }

    element = queue_object->storage[queue_object->front];
    queue_object->storage[queue_object->front] = SENTINEL;

    if (queue_object->front == queue_object->length - 1) {
        queue_object->front = 0;
    } else {
        queue_object->front += 1;
    }

    pthread_cond_signal(queue_object->queue_has_space);
    pthread_mutex_unlock(queue_object->mutex);
    return element;
}

void display_contents(struct queue *queue_object)
{
    for (int i = 0; i < queue_object->length; i++) {
        printf("%d ", queue_object->storage[i]);
    }
    printf("\n");
}

bool is_queue_full(struct queue *queue_object)
{
    return (queue_object->front == queue_object->rear &&
            queue_object->storage[queue_object->front] != SENTINEL);
}

bool is_queue_empty(struct queue *queue_object)
{
    return (queue_object->rear == queue_object->front &&
            queue_object->storage[queue_object->front] == SENTINEL);
}
