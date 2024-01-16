#include "lib/queue_list.h"

#include <assert.h>

void
destroy(queue *queue) {
    node *ptr = queue->list->head;

    while (ptr) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    free(queue->list);
    free(queue);
}

void
debug(queue *queue) {
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

int
main(int argc, char **argv) {
    queue *myqueue = make_queue();
    debug(myqueue);

    assert(myqueue->empty(myqueue) == true);
    for (int i = 1; i <= 6; i++) {
        myqueue->enqueue(myqueue, i);
    }
    debug(myqueue);

    assert(myqueue->empty(myqueue) == 0);

    for (int i = 1; i <= 4; i++) {
        assert(myqueue->dequeue(myqueue) == i);
    }
    debug(myqueue);
    assert(myqueue->dequeue(myqueue) == 5);
    assert(myqueue->dequeue(myqueue) == 6);
    assert(myqueue->empty(myqueue) == true);

    destroy(myqueue);
    return 0;
}
