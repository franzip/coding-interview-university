#include "lib/queue_array.h"

#include <assert.h>

int
main(int argc, char **argv) {
    queue *myqueue = make_queue();
    assert(myqueue->full(myqueue) == false);
    assert(myqueue->empty(myqueue) == true);
    assert(myqueue->dequeue(myqueue) == -1);
    debug_queue(myqueue);

    for (int i = 1; i < ARRAY_CAPACITY; i++) {
        assert(myqueue->enqueue(myqueue, i) == 0);
    }

    debug_queue(myqueue);

    assert(myqueue->empty(myqueue) == false);
    assert(myqueue->enqueue(myqueue, 15) == 0);
    debug_queue(myqueue);
    assert(myqueue->full(myqueue) == true);
    assert(myqueue->enqueue(myqueue, 100) == -1);

    for (int i = 1; i < ARRAY_CAPACITY; i++) {
        assert(myqueue->dequeue(myqueue) == i);
    }

    debug_queue(myqueue);
    assert(myqueue->empty(myqueue) == 0);
    assert(myqueue->dequeue(myqueue) == 15);
    assert(myqueue->empty(myqueue) == true);
    debug_queue(myqueue);
    assert(myqueue->dequeue(myqueue) == -1);

    free(myqueue->items);
    free(myqueue);
    return 0;
}
