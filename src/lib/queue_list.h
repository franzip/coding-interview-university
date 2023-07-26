#include "linked_list.h"

typedef struct Queue queue;

struct Queue {
    linkedlist *list;
    void (*enqueue)(queue *, int);
    int (*dequeue)(queue *);
    bool (*empty)(queue *);
};

void
enqueue(queue *queue, int val) {
    queue->list->push_back(queue->list, val);
    return;
}

int
dequeue(queue *queue) {
    if (queue->empty(queue)) {
        return -1;
    }
    return queue->list->pop_front(queue->list);
}

bool
emptyq(queue *queue) {
    return queue->list->empty(queue->list);
}

queue *
make_queue() {
    queue *myqueue = (queue *) malloc(sizeof(queue));
    linkedlist *list = make_linked_list();
    myqueue->list = list;
    myqueue->enqueue = enqueue;
    myqueue->dequeue = dequeue;
    myqueue->empty = emptyq;

    return myqueue;
}
