#include "linked_list.c"

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
    return queue->list->pop_front(queue->list);
}

bool
emptyq(queue *queue) {
    return queue->list->empty(queue->list);
}

queue *
make_queue() {
    queue *myqueue = malloc(sizeof(queue));
    linkedlist *list = make_list();
    myqueue->list = list;
    myqueue->enqueue = enqueue;
    myqueue->dequeue = dequeue;
    myqueue->empty = emptyq;

    return myqueue;
}

int
main(int argc, char **argv) {
    queue *myqueue = make_queue();
    printf("empty: %d\n", myqueue->empty(myqueue));
    for (int i = 1; i <= 5; i++) {
        myqueue->enqueue(myqueue, i);
    }
    printf("empty: %d\n", myqueue->empty(myqueue));

    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    myqueue->enqueue(myqueue, 15);
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
    printf("%d\n", myqueue->dequeue(myqueue));
}
