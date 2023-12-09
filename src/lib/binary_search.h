#include "stdio.h"

int
bin_search(int *list, int target, int size) {
    int left = 0;
    int right = size;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (list[mid] == target) {
            return mid;
        } else if (list[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int
rec_bin_search(int *list, int target, int left, int right) {
    if (left == right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (list[mid] == target) {
        return mid;
    }

    return list[mid] < target ? rec_bin_search(list, target, mid + 1, right)
                              : rec_bin_search(list, target, left, mid - 1);
}
