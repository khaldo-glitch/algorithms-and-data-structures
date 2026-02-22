#include "sorting.h"

// This swap is specific to quicksort and works on ints.
// Made static to avoid conflicts with other swap functions (e.g., in heap.h).
static void swap_int(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// This is a variant of Hoare partition that places the pivot at the correct position
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    int j = right; // Start at right, will decrement immediately

    while (1) {
        // Find element on left that should be on right
        do {
            i++;
        } while (arr[i] < pivot);

        // Find element on right that should be on left
        do {
            j--;
        } while (j >= left && arr[j] >= pivot);

        if (i >= j) {
            swap_int(&arr[i], &arr[right]); // Place pivot in correct position
            return i;
        }

        swap_int(&arr[i], &arr[j]);
    }
}

void quick_sort(int arr[], int left, int right) {
    if (left < right) {
        int p = partition(arr, left, right);
        quick_sort(arr, left, p - 1);
        quick_sort(arr, p + 1, right);
    }
}
