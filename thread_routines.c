#include <stdio.h>
#include "queue.h"

int enqueue_item(int item)
{
    printf("Enqueueing %d\n", item);
    return enqueue(shared_queue, item);
}

int dequeue_item()
{
    int item;

    item = dequeue(shared_queue);
    printf("Dequeuing %d\n", item);
    return item;
}
