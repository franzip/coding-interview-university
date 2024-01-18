#include "lib/heap.h"

#include <assert.h>
#include <time.h>

int
main(int argc, char const* argv[]) {
    srand(time(NULL));

    heap* my_heap = make_heap();

    assert(my_heap->get_size(my_heap) == 0);
    assert(my_heap->is_empty(my_heap) == true);
    my_heap->insert(my_heap, 5);
    my_heap->insert(my_heap, 3);
    my_heap->insert(my_heap, 51);
    my_heap->insert(my_heap, 8);
    my_heap->insert(my_heap, 10);
    my_heap->print(my_heap);
    assert(my_heap->get_size(my_heap) == 5);
    assert(my_heap->is_empty(my_heap) == false);
    assert(my_heap->get_max(my_heap) == 51);
    assert(my_heap->extract_max(my_heap) == 51);
    my_heap->print(my_heap);
    assert(my_heap->get_max(my_heap) == 10);
    assert(my_heap->extract_max(my_heap) == 10);
    assert(my_heap->get_size(my_heap) == 3);
    my_heap->sort(my_heap);
    my_heap->print(my_heap);

    vector* vec = make_vector();
    int vec_size = 10;

    for (int i = 0; i < vec_size; i++) {
        vec->push(vec, rand() % 10);
    }

    vec->print(vec);
    heap_sort(vec, vec_size);
    printf("sorted: \n");
    vec->print(vec);
}
