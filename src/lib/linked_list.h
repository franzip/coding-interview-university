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
        return -1;
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
        return -1;
    }

    node *ptr = list->head;

    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }

    return ptr->value;
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
        return -1;
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
        return -1;
    }

    return list->head->value;
}

int
back(linkedlist *list) {
    if (list->tail == NULL) {
        return -1;
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

    list->l_size--;
    prev->next = ptr->next;
    free(ptr);
}

int
value_n_from_end(linkedlist *list, size_t from_end) {
    if (from_end < 0 || from_end >= list->l_size) {
        return -1;
    }

    if (from_end == 0) {
        from_end++;
    }

    node *ptr = list->head;

    for (int i = 0; i < list->l_size - from_end; i++) {
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
debug_list(linkedlist *list) {
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

linkedlist *
make_linked_list() {
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
    return list;
};
