#include "sorting.h"
#include "heap.h"

// Sorts an array of item_t structs in-place based on their 'key'.
void heap_sort(item_t* A, int n) {
    heap_t h;
    h.A = A;
    h.size = n;
    h.capacity = n;

    heap_build(&h);

    for (int i = n - 1; i > 0; i--) {
        swap(&h.A[0], &h.A[i]);
        h.size--;
        heapify(&h, 0);
    }
}
