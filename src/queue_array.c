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

    queue->items[queue->write_ptr++] = val;

    return 0;
}

int
dequeue(queue *queue) {
    if (queue->empty(queue)) {
        return -1;
    }

    return queue->items[queue->read_ptr++];
}

bool
empty(queue *queue) {
    return queue->write_ptr == queue->read_ptr;
}

bool
full(queue *queue) {
    return ((queue->write_ptr + 1) % ARRAY_CAPACITY) ==
           ((queue->read_ptr) % ARRAY_CAPACITY);
}

queue *
make_queue() {
    queue *myqueue = malloc(sizeof(queue));
    int *items = malloc(ARRAY_CAPACITY * sizeof(int));
    for (int i = 0; i < ARRAY_CAPACITY; i++) {
        items[i] = 0;
    }
    myqueue->items = items;
    myqueue->read_ptr = 0;
    myqueue->write_ptr = 0;
    myqueue->enqueue = enqueue;
    myqueue->dequeue = dequeue;
    myqueue->empty = empty;
    myqueue->full = full;

    return myqueue;
}

int
main(int argc, char **argv) {
    queue *myqueue = make_queue();
    printf("full: %d\n", myqueue->full(myqueue));
    printf("empty: %d\n", myqueue->empty(myqueue));
    printf("enqueing...\n");
    for (int i = 0; i < ARRAY_CAPACITY - 2; i++) {
        myqueue->enqueue(myqueue, i);
    }
    printf("empty: %d\n", myqueue->empty(myqueue));
    printf("full: %d\n", myqueue->full(myqueue));

    myqueue->enqueue(myqueue, 15);
    printf("full: %d\n", myqueue->full(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    free(myqueue->items);
}
