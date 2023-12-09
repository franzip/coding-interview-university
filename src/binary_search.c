#include "lib/binary_search.h"

#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

int
main(int argc, char **argv) {
    int size = 10000;
    int *nums = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        nums[i] = i;
    }

    assert(bin_search(nums, 840, size) == 840);
    assert(rec_bin_search(nums, 840, 0, size));
    free(nums);
}
