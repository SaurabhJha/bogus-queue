#define MAX_PRODUCER_THREADS 100

#define MAX_CONSUMER_THREADS 100

int enqueue_item(int item);

int dequeue_item();

int fib(int number);

extern const int shared_data[100];
