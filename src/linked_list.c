#include "lib/linked_list.h"

int
main(int argc, char **argv) {
    linkedlist *list = make_list();

    printf("%d\n", list->size(list));
    printf("%d\n", list->empty(list));
    list->push_front(list, 5);
    list->push_front(list, 15);
    printf("%d\n", list->value_at(list, 0));
    printf("%d\n", list->value_at(list, 1));
    printf("popping head: %d\n", list->pop_front(list));
    list->push_front(list, 10);
    list->push_front(list, 20);
    list->push_front(list, 30);
    list->debug(list);
    printf("front: %d\n", list->front(list));
    printf("back: %d\n", list->back(list));
    printf("popping back: %d\n", list->pop_back(list));
    list->debug(list);
    printf("popping back: %d\n", list->pop_back(list));
    list->debug(list);
    printf("inserting %d at index %d\n", 1, 2);
    list->insert(list, 2, 1);
    list->debug(list);
    printf("inserting %d at index %d\n", 15, 1);
    list->insert(list, 1, 15);
    list->debug(list);
    printf("inserting %d at index %d\n", 50, 2);
    list->insert(list, 2, 50);
    list->debug(list);
    printf("erasing element at index %d:\n", 0);
    list->erase(list, 0);
    list->debug(list);
    printf("erasing element at index %d:\n", list->size(list));
    list->erase(list, list->size(list));
    list->debug(list);
    printf("erasing element at index %d:\n", 1);
    list->erase(list, 1);
    list->debug(list);
    list->push_front(list, 50);
    list->debug(list);
    printf("remove_value %d\n", 15);
    list->remove_value(list, 15);
    list->debug(list);
    list->push_front(list, 5);
    list->push_front(list, 15);
    list->debug(list);
    printf("value_n_from_end - %d: %d\n", 1, list->value_n_from_end(list, 1));
    printf("value_n_from_end - %d: %d\n", 3, list->value_n_from_end(list, 3));
    list->debug(list);
    printf("reversing list\n");
    list->reverse(list);
    list->debug(list);
    list->destroy(list);
    return 0;
}
