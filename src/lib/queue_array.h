#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_CAPACITY 8

typedef struct Queue queue;

struct Queue {
    int read_ptr;
    int write_ptr;
    int *items;
    int (*enqueue)(queue *, int);
    int (*dequeue)(queue *);
    bool (*empty)(queue *);
    bool (*full)(queue *);
};

int
enqueue(queue *queue, int val) {
    if (queue->full(queue)) {
        return -1;
    }

    queue->write_ptr = (queue->write_ptr + 1) % ARRAY_CAPACITY;
    queue->items[queue->write_ptr] = val;

    return 0;
}

int
dequeue(queue *queue) {
    if (queue->empty(queue)) {
        return -1;
    }

    queue->read_ptr = (queue->read_ptr + 1) % ARRAY_CAPACITY;
    int val = queue->items[queue->read_ptr];
    queue->items[queue->read_ptr] = 0;

    return val;
}

bool
empty(queue *queue) {
    return queue->write_ptr == queue->read_ptr;
}

bool
full(queue *queue) {
    if (queue->read_ptr == -1) {
        return queue->write_ptr + 1 == ARRAY_CAPACITY;
    }

    return ((queue->write_ptr + 1) % ARRAY_CAPACITY) == queue->read_ptr;
}

queue *
make_queue() {
    queue *myqueue = (queue *) malloc(sizeof(queue));
    int *items = (int *) malloc(ARRAY_CAPACITY * sizeof(int));

    myqueue->items = items;
    myqueue->read_ptr = -1;
    myqueue->write_ptr = -1;
    myqueue->enqueue = enqueue;
    myqueue->dequeue = dequeue;
    myqueue->empty = empty;
    myqueue->full = full;

    return myqueue;
}
