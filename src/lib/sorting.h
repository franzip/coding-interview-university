#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int
median_of_three(int a, int b, int c) {
    if ((a > b) ^ (a > c))
        return a;
    else if ((b < a) ^ (b < c))
        return b;
    else
        return c;
}

void
swap(int* input, int a, int b) {
    int tmp = input[a];
    input[a] = b;
    input[b] = tmp;
}

void
bubble_sort(int array[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int swapped = false;

        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swap(array, j, j + 1);
                swapped = true;
            }
        }

        if (swapped == 0) {
            break;
        }
    }
}

void
selection_sort(int* input, int length) {
    for (int i = 0; i < length - 1; i++) {
        int min_idx = input[i];

        for (int j = i + 1; j < length; j++) {
            if (input[j] < min_idx) {
                min_idx = input[j];
            }
        }

        if (i != min_idx) {
            swap(input, i, min_idx);
        }
    }
}

void
insertion_sort(int* input, int length) {
    for (int i = 1; i < length; i++) {
        int curr = input[i];
        int j = i - 1;

        while (j >= 0 && curr < input[j]) {
            input[j + 1] = input[j];
            j--;
        }

        input[j + 1] = curr;
    }
}

void
merge(int* left, int left_len, int* right, int right_len, int* output) {
    int i;
    int j;
    int iout;

    i = j = iout = 0;

    while (i < left_len && j < right_len) {
        if (left[i] < right[j]) {
            output[iout++] = left[i++];
        } else {
            output[iout++] = right[j++];
        }
    }

    while (i < left_len) {
        output[iout++] = left[i++];
    }

    while (j < right_len) {
        output[iout++] = right[j++];
    }
}

void
merge_sort(int* input, int* output, int length) {
    if (length < 2) {
        memcpy(output, input, sizeof(int) * length);
        return;
    }

    int left_len = (length / 2);
    int right_len = (length - (length / 2));

    int* left = malloc(sizeof(int) * left_len);
    int* right = malloc(sizeof(int) * right_len);

    merge_sort(input, left, left_len);
    merge_sort(input + left_len, right, right_len);

    merge(left, left_len, right, right_len, output);

    free(left);
    free(right);
}

int
partition(int* input, int low, int high) {
    int pivot = input[rand() % high];

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (input[j] <= pivot) {
            i++;
            swap(input, i, j);
        }
    }

    swap(input, i + 1, high);

    return (i + 1);
}

void
quick_sort(int* input, int low, int high) {
    if (low < high) {
        int pi = partition(input, low, high);

        quick_sort(input, low, pi - 1);
        quick_sort(input, pi + 1, high);
    }
}
