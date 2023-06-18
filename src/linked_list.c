#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;
typedef struct LinkedList linkedlist;

struct Node {
    int value;
    node *next;
};

struct LinkedList {
    size_t l_size;
    node *head;
    node *tail;
    int (*size)(linkedlist *);
    bool (*empty)(linkedlist *);
    int (*value_at)(linkedlist *, size_t);
    void (*push_front)(linkedlist *, int);
    int (*pop_front)(linkedlist *);
    void (*push_back)(linkedlist *, int);
    int (*pop_back)(linkedlist *);
    int (*front)(linkedlist *);
    int (*back)(linkedlist *);
    void (*insert)(linkedlist *, size_t, int);
    void (*erase)(linkedlist *, size_t);
    int (*value_n_from_end)(linkedlist *, size_t);
    void (*reverse)(linkedlist *);
    void (*remove_value)(linkedlist *, int);
    void (*debug)(linkedlist *);
    void (*destroy)(linkedlist *);
};

int
size(linkedlist *list) {
    return list->l_size;
}

bool
empty(linkedlist *list) {
    return list->l_size == 0;
}

void
push_front(linkedlist *list, int val) {
    node *new_head = malloc(sizeof(node));
    new_head->value = val;

    if (list->head == NULL) {
        list->head = new_head;
        list->tail = new_head;
    } else {
        new_head->next = list->head;
        list->head = new_head;
    }

    list->l_size++;
}

int
pop_front(linkedlist *list) {
    node *head = list->head;

    if (head == NULL) {
        perror("Something went wrong");
        exit(1);
    }

    int value = head->value;
    node *next = head->next;

    if (next == NULL) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = next;
        head->next = NULL;
        free(head);
    }

    list->l_size--;

    return value;
}

int
value_at(linkedlist *list, size_t index) {
    if (index > list->l_size) {
        perror("Something went wrong");
        exit(1);
    }

    node *ptr = list->head;

    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }

    return ptr->value;
}

void
debug(linkedlist *list) {
    node *head = list->head;
    int i = 0;
    printf("Debugging list:\n");
    while (head) {
        printf("%d: %d\n", i, head->value);
        head = head->next;
        i++;
    }
}

void
push_back(linkedlist *list, int val) {
    node *new_tail = malloc(sizeof(node));

    new_tail->value = val;

    if (list->tail == NULL) {
        list->tail = new_tail;
        list->head = new_tail;
    } else {
        list->tail->next = new_tail;
        list->tail = new_tail;
    }

    list->l_size++;
}

int
pop_back(linkedlist *list) {
    node *tail = list->tail;

    if (tail == NULL) {
        perror("Something went wrong");
        exit(1);
    }

    int value = tail->value;
    node *new_tail = list->head;

    while (new_tail->next != tail) {
        new_tail = new_tail->next;
    }

    new_tail->next = NULL;
    free(tail);
    list->tail = new_tail;

    list->l_size--;

    return value;
}

int
front(linkedlist *list) {
    if (list->head == NULL) {
        perror("Something went wrong");
        exit(1);
    }

    return list->head->value;
}

int
back(linkedlist *list) {
    if (list->tail == NULL) {
        perror("Something went wrong");
        exit(1);
    }

    return list->tail->value;
}

void
insert(linkedlist *list, size_t index, int value) {
    if (index > list->l_size) {
        perror("Something went wrong");
        exit(1);
    }

    if (index == 0) {
        list->push_front(list, value);
        return;
    }

    if (index == list->l_size) {
        list->push_back(list, value);
        return;
    }

    node *new_node = malloc(sizeof(node));
    new_node->value = value;

    node *prev = list->head;
    node *next = prev->next;

    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
        next = next->next;
    }

    new_node->next = next;
    prev->next = new_node;
    list->l_size++;
}

void
remove_value(linkedlist *list, int value) {
    node *ptr = list->head;
    node *prev;
    int i = 0;

    while (ptr) {
        if (ptr->value == value) {
            break;
        }
        prev = ptr;
        ptr = ptr->next;
        i += 1;
    }

    if (i == list->l_size) {
        return;
    }

    if (i == 0) {
        list->pop_front(list);
        return;
    }

    if (i == list->l_size - 1) {
        list->pop_back(list);
        return;
    }

    prev->next = ptr->next;
    free(ptr);
}

int
value_n_from_end(linkedlist *list, size_t fromEnd) {
    if (fromEnd < 0 || fromEnd >= list->l_size) {
        perror("Something went wrong");
        exit(1);
    }

    if (fromEnd == 0) {
        fromEnd++;
    }

    node *ptr = list->head;

    for (int i = 0; i < list->l_size - fromEnd - 1; i++) {
        ptr = ptr->next;
    }

    return ptr->value;
}

void
erase(linkedlist *list, size_t index) {
    if (index > list->l_size) {
        perror("Something went wrong");
        exit(1);
    }

    if (index == 0) {
        list->pop_front(list);
        return;
    }

    if (index == list->l_size) {
        list->pop_back(list);
        return;
    }

    node *prev = list->head;
    node *next = prev->next;

    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
        next = next->next;
    }

    prev->next = next->next;
    free(next);

    list->l_size--;
}

void
reverse(linkedlist *list) {
    node *curr = list->head;
    node *prev = NULL;
    if (curr == NULL) {
        return;
    }

    while (curr) {
        node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->tail = list->head;
    list->head = prev;
}

void
destroy(linkedlist *list) {
    node *ptr = list->head;

    while (ptr) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

linkedlist *
make_list() {
    linkedlist *list = malloc(sizeof(linkedlist));
    list->l_size = 0;

    list->head = NULL;
    list->tail = NULL;
    list->size = size;
    list->empty = empty;
    list->value_at = value_at;
    list->push_front = push_front;
    list->pop_front = pop_front;
    list->push_back = push_back;
    list->pop_back = pop_back;
    list->front = front;
    list->back = back;
    list->insert = insert;
    list->erase = erase;
    list->remove_value = remove_value;
    list->value_n_from_end = value_n_from_end;
    list->reverse = reverse;
    list->debug = debug;
    list->destroy = destroy;
    return list;
};

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
