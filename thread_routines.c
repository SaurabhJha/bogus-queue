#include <syslog.h>
#include "queue.h"
#include "thread_routines.h"

int enqueue_item(int item)
{
    syslog(LOG_INFO, "Enqueueing %d\n", item);
    return enqueue(shared_queue, item);
}

int dequeue_item()
{
    int item;

    item = dequeue(shared_queue);
    syslog(LOG_INFO, "Fibonacci of %d is %d\n", item, fib(item));
    return item;
}

int fib(int number)
{
    if (number == 0 || number == 1) {
        return number;
    } else {
        return fib(number - 1) + fib(number - 2);
    }
}
