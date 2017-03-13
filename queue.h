#include <pthread.h>
#include <stdbool.h>


/* This is problem specific. We won't have have negative integers in
   our Queue. */
#define SENTINEL -100

struct queue {
    /* State variables */
    int *storage;
    int front; /* Front of the queue. Should have element
                  when queue has at least one. */
    int rear; /* Next free slot. Should not have element unless the queue is
                 full */
    int length;

    /* Synchronization variables */
    pthread_mutex_t *mutex;
    pthread_cond_t *queue_has_space;
    pthread_cond_t *queue_has_element;
};

struct queue *initialize_queue(int queue_length);

void destruct_queue(struct queue *queue_object);

bool enqueue(struct queue *queue_object, int element);

int dequeue(struct queue *queue_object);

void display_contents(struct queue *queue_object);

bool is_queue_empty(struct queue *queue_object);

bool is_queue_full(struct queue *queue_object);

#define QUEUE_SIZE 10

/* Shared queue */
struct queue *shared_queue;
