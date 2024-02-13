#include "lib/sorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VAL 1000
#define MIN_VAL 0

int*
make_rand_array(int length) {
    int* out = malloc(length * sizeof(int));

    for (int i = 0; i < length; i++) {
        out[i] = rand() % (MAX_VAL - MIN_VAL + 1) + MIN_VAL;
    }

    return out;
}

void
assert_array_sorted(int* in, int length) {
    for (int i = 1, prev = in[0]; i < length; i++) {
        assert(in[i] >= prev);
    }
}

void
debug(int* in, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", in[i]);
    }
    printf("\n");
}

int
main(int argc, char const* argv[]) {
    srand(time(0));
    int length = 1000;
    int* array = make_rand_array(length);

    bubble_sort(array, length);
    assert_array_sorted(array, length);

    array = make_rand_array(length);
    selection_sort(array, length);
    assert_array_sorted(array, length);

    array = make_rand_array(length);
    insertion_sort(array, length);
    assert_array_sorted(array, length);

    array = make_rand_array(length);
    int* sorted = malloc(sizeof(int) * length);
    merge_sort(array, sorted, length);
    assert_array_sorted(sorted, length);

    array = make_rand_array(length);
    quick_sort(array, 0, length);
    assert_array_sorted(sorted, length);

    free(array);
    free(sorted);
}
