#include "lib/linked_list.h"

#include <assert.h>

void
destroy(linkedlist *list) {
    node *ptr = list->head;

    while (ptr) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    free(list);
}

void
debug(linkedlist *list) {
    node *head = list->head;
    int i = 0;
    printf("list: [");
    while (head) {
        printf("%d", head->value);
        if (i < list->size(list) - 1) {
            printf(" -> ");
        }
        head = head->next;
        i++;
    }
    printf("]\n");
}

int
main(int argc, char **argv) {
    int size;

    linkedlist *list = make_linked_list();
    assert(list->size(list) == 0);
    assert(list->empty(list) == 1);
    assert(list->pop_back(list) == -1);
    assert(list->pop_front(list) == -1);
    assert(list->front(list) == -1);
    assert(list->back(list) == -1);

    list->push_front(list, 5);
    list->push_front(list, 15);
    debug(list);
    assert(list->empty(list) == 0);
    assert(list->size(list) == 2);
    assert(list->value_at(list, 0) == 15);
    assert(list->value_at(list, 1) == 5);
    assert(list->value_at(list, 1000) == -1);

    assert(list->pop_front(list) == 15);
    list->push_front(list, 10);
    list->push_front(list, 20);
    list->push_front(list, 30);
    debug(list);
    assert(list->front(list) == 30);
    assert(list->back(list) == 5);
    assert(list->pop_back(list) == 5);
    assert(list->pop_back(list) == 10);

    list->insert(list, 2, 1);
    list->insert(list, 1, 15);
    list->insert(list, 2, 50);
    assert(list->size(list) == 5);
    assert(list->value_at(list, 2) == 50);

    debug(list);
    printf("erasing element at index %d:\n", 0);
    assert(list->value_at(list, 0) == 30);
    list->erase(list, 0);
    assert(list->value_at(list, 0) != 30);
    assert(list->size(list) == 4);

    size = list->size(list);
    printf("erasing element at index %d:\n", size);
    list->erase(list, size);
    assert(list->value_at(list, size) == -1);
    assert(list->size(list) == 3);
    debug(list);

    list->push_front(list, 35);
    list->push_front(list, 40);
    debug(list);
    printf("remove_value %d\n", 50);
    assert(list->value_at(list, 3) == 50);
    list->remove_value(list, 50);

    list->push_front(list, 5);
    list->push_front(list, 15);
    debug(list);

    assert(list->value_n_from_end(list, 1) == 20);
    assert(list->value_n_from_end(list, 2) == 15);
    assert(list->value_n_from_end(list, 1000) == -1);

    printf("reversing list\n");
    list->reverse(list);
    debug(list);
    destroy(list);
    return 0;
}
