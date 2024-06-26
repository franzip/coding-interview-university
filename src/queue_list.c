#include "lib/queue_list.h"

#include <assert.h>

void
destroy(queue *queue) {
    list_node *ptr = queue->list->head;

    while (ptr) {
        list_node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    free(queue->list);
    free(queue);
}

int
main(int argc, char **argv) {
    queue *myqueue = make_queue();
    debug_queue_list(myqueue);

    assert(myqueue->empty(myqueue) == true);
    for (int i = 1; i <= 6; i++) {
        myqueue->enqueue(myqueue, i);
    }
    debug_queue_list(myqueue);

    assert(myqueue->empty(myqueue) == 0);

    for (int i = 1; i <= 4; i++) {
        assert(myqueue->dequeue(myqueue) == i);
    }
    debug_queue_list(myqueue);
    assert(myqueue->dequeue(myqueue) == 5);
    assert(myqueue->dequeue(myqueue) == 6);
    assert(myqueue->empty(myqueue) == true);

    destroy(myqueue);
    return 0;
}
