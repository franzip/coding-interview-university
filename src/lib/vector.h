#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

typedef struct Vector vector;
struct Vector {
    int *items;
    size_t capacity;
    size_t length;
    bool (*is_empty)(vector *);
    int (*at)(vector *, size_t);
    void (*push)(vector *, int);
    void (*insert)(vector *, size_t, int);
    void (*prepend)(vector *, int);
    int (*pop)(vector *);
    int (*delete)(vector *, size_t);
    void (*remove)(vector *, int);
    int (*find)(vector *, int);
};

void
resize(vector *v) {
    size_t new_capacity = v->capacity * 2;
    v->items = realloc(v->items, new_capacity * sizeof(int));
    v->capacity = new_capacity;
}

bool
is_empty(vector *v) {
    return v->length == 0;
}

int
at(vector *v, size_t index) {
    if (index > v->capacity) {
        perror("Something went wrong");
        exit(1);
    }

    int *ptr = v->items + index;

    return *ptr;
}

void
push(vector *v, int item) {
    if (v->length >= v->capacity) {
        resize(v);
    }
    int *ptr = v->items + v->length;
    *ptr = item;

    v->length++;
}

void
prepend(vector *v, int item) {
    v->insert(v, 0, item);
}

void
insert(vector *v, size_t index, int item) {
    if (index > v->capacity) {
        perror("Something went wrong");
        exit(1);
    }

    if (v->length >= v->capacity) {
        resize(v);
    }

    int *ptr = v->items + v->length;

    while (ptr != v->items + index) {
        *ptr = *(ptr - 1);
        ptr--;
    }
    ptr = v->items + index;
    *ptr = item;
    v->length++;
}

int delete(vector *v, size_t index) {
    int *ptr;
    int val;
    ptr = v->items + index;
    val = *ptr;

    while (ptr != v->items + v->length) {
        *ptr = *(ptr + 1);
        ptr++;
    }

    v->length--;
    return val;
}

int
pop(vector *v) {
    int item = v->delete (v, v->length - 1);
    if (v->length * 4 <= v->capacity) {
        int new_capacity = v->capacity / 2;
        v->items = realloc(v->items, new_capacity * sizeof(int));
        v->capacity = new_capacity;
    }
    return item;
}

void
remove_el(vector *v, int item) {
    int *ptr = v->items;
    while (ptr != v->items + v->length) {
        if (*ptr == item) {
            *ptr = 0;
        }
        ptr++;
    }
}

int
find(vector *v, int needle) {
    int *ptr = v->items;
    int idx = 0;

    while (ptr != v->items + v->length) {
        if (*ptr == needle) {
            return idx;
        }
        idx++;
        ptr++;
    }

    return -1;
}

vector *
make_vector() {
    vector *vec = malloc(sizeof(vector));
    int *items = malloc(INITIAL_CAPACITY * sizeof(int));
    for (int i = 0; i < INITIAL_CAPACITY; i++) {
        items[i] = 0;
    }
    vec->capacity = INITIAL_CAPACITY;
    vec->length = 0;
    vec->items = items;
    vec->is_empty = is_empty;
    vec->at = at;
    vec->push = push;
    vec->insert = insert;
    vec->prepend = prepend;
    vec->pop = pop;
    vec->delete = delete;
    vec->remove = remove_el;
    vec->find = find;

    return vec;
}
