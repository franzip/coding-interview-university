#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "vector.h"

typedef struct Heap heap;

struct Heap {
    vector *items;
    size_t size;
    size_t (*get_size)(heap *);
    bool (*is_empty)(heap *);
    int (*get_max)(heap *);
    int (*extract_max)(heap *);
    void (*insert)(heap *, int);
    void (*remove)(heap *, size_t);
    void (*sort)(heap *);
    void (*print)(heap *);
};

void
_swap(vector *items, size_t first_idx, size_t second_idx) {
    int first = items->at(items, first_idx);
    int second = items->at(items, second_idx);
    items->items[first_idx] = second;
    items->items[second_idx] = first;
}

int
_get_parent(size_t index) {
    return floor((index - 1) / 2);
}

int
_get_left_child(size_t index) {
    return (2 * index) + 1;
}

int
_get_right_child(size_t index) {
    return (2 * index) + 2;
}

void
_sift_up(vector *items, size_t index) {
    if (index == 0) {
        return;
    }

    int parent_idx = _get_parent(index);
    int current = items->at(items, index);
    int parent = items->at(items, parent_idx);
    if (current > parent) {
        _swap(items, index, parent_idx);
        _sift_up(items, parent_idx);
    }
}

void
_sift_down(vector *items, size_t index, int heap_size) {
    int left_idx = _get_left_child(index);
    int right_idx = _get_right_child(index);

    if (index >= heap_size || left_idx >= heap_size || right_idx >= heap_size) {
        return;
    }

    int current = items->at(items, index);
    int left = items->at(items, left_idx);
    int right = items->at(items, right_idx);

    if (left > right && current < left) {
        _swap(items, index, left_idx);
        _sift_down(items, left_idx, heap_size);
    } else if (right > left && current < right) {
        _swap(items, index, right_idx);
        _sift_down(items, right_idx, heap_size);
    }
}

size_t
get_size(heap *hheap) {
    return hheap->size;
}

bool
is_heap_empty(heap *hheap) {
    return hheap->get_size(hheap) == 0;
}

int
get_max(heap *hheap) {
    if (hheap->is_empty(hheap)) {
        perror("Heap is empty\n");
        exit(1);
    }
    return hheap->items->at(hheap->items, 0);
}

int
extract_max(heap *hheap) {
    if (hheap->is_empty(hheap)) {
        perror("Heap is empty \n");
        exit(1);
    }

    vector *items = hheap->items;
    int max = hheap->get_max(hheap);
    int heap_size = hheap->get_size(hheap);

    if (heap_size == 1) {
        hheap->size--;
        return max;
    }

    items->items[0] = items->at(items, heap_size - 1);
    items->items[heap_size - 1] = max;
    _sift_down(hheap->items, 0, --hheap->size);
    return max;
}

void
insert_into_heap(heap *hheap, int value) {
    hheap->items->push(hheap->items, value);
    hheap->size++;
    _sift_up(hheap->items, hheap->size - 1);
}

void
remove_from_heap(heap *hheap, size_t idx) {
    int heap_size = hheap->get_size(hheap);

    if (idx >= heap_size) {
        perror("Invalid index");
        exit(1);
    }

    hheap->items->items[idx] = INT32_MAX;
    _sift_up(hheap->items, idx);
    hheap->extract_max(hheap);
}

void
sort(heap *hheap) {
    for (int i = 0; i < hheap->get_size(hheap); i++) {
        hheap->extract_max(hheap);
    }
}

void
_heapify(vector *items, size_t index, size_t size) {
    int largest = index;

    int left = _get_left_child(index);
    int right = _get_right_child(index);

    if (left < size && items->at(items, left) > items->at(items, largest)) {
        largest = left;
    }

    if (right < size && items->at(items, right) > items->at(items, largest)) {
        largest = right;
    }

    if (largest != index) {
        _swap(items, index, largest);
        _heapify(items, largest, size);
    }
}

void
heap_sort(vector *items, size_t size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        _heapify(items, i, size);
    }

    for (int i = size - 1; i >= 0; i--) {
        _swap(items, 0, i);
        _heapify(items, 0, i);
    }
}

void
print_heap(heap *hheap) {
    vector *items = hheap->items;
    int used = hheap->get_size(hheap);
    int total = items->length;
    printf("heap (used): [");
    for (int i = 0; i < used; i++) {
        printf("%d", items->at(items, i));
        if (i + 1 < used) {
            printf(", ");
        }
    }
    printf("]");
    if (used != total) {
        printf(" | (left): [");
        for (int i = used; i < total; i++) {
            printf("%d", items->at(items, i));
            if (i + 1 < total) {
                printf(", ");
            }
        }
        printf("]");
    }
    printf("\n");
}

heap *
make_heap() {
    heap *new_heap = (heap *) malloc(sizeof(heap));
    new_heap->items = make_vector();
    new_heap->size = 0;
    new_heap->get_size = get_size;
    new_heap->is_empty = is_heap_empty;
    new_heap->insert = insert_into_heap;
    new_heap->get_max = get_max;
    new_heap->extract_max = extract_max;
    new_heap->remove = remove_from_heap;
    new_heap->sort = sort;
    new_heap->print = print_heap;

    return new_heap;
}
