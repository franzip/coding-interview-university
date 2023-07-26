#include "lib/queue_array.h"

#include <assert.h>

void
debug(queue *queue) {
    printf("queue: [");
    for (int i = 0; i < ARRAY_CAPACITY; i++) {
        printf("%d", queue->items[i]);
        if (i < ARRAY_CAPACITY - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void
destroy(queue *queue) {
    free(queue->items);
    free(queue);
}

int
main(int argc, char **argv) {
    queue *myqueue = make_queue();
    assert(myqueue->full(myqueue) == 0);
    assert(myqueue->empty(myqueue) == 1);
    assert(myqueue->dequeue(myqueue) == -1);
    debug(myqueue);

    for (int i = 1; i < ARRAY_CAPACITY; i++) {
        assert(myqueue->enqueue(myqueue, i) == 0);
    }

    debug(myqueue);

    assert(myqueue->empty(myqueue) == 0);
    assert(myqueue->enqueue(myqueue, 15) == 0);
    debug(myqueue);
    assert(myqueue->full(myqueue) == 1);
    assert(myqueue->enqueue(myqueue, 100) == -1);

    for (int i = 1; i < ARRAY_CAPACITY; i++) {
        assert(myqueue->dequeue(myqueue) == i);
    }

    debug(myqueue);
    assert(myqueue->empty(myqueue) == 0);
    assert(myqueue->dequeue(myqueue) == 15);
    assert(myqueue->empty(myqueue) == 1);
    debug(myqueue);
    assert(myqueue->dequeue(myqueue) == -1);

    destroy(myqueue);
}
