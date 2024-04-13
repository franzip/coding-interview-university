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

void
debug_queue_list(queue *queue) {
    node *head = queue->list->head;
    int i = 0;
    printf("list: [");
    while (head) {
        printf("%d", head->value);
        if (i < queue->list->size(queue->list) - 1) {
            printf(" -> ");
        }
        head = head->next;
        i++;
    }
    printf("]\n");
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
