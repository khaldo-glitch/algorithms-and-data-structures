//
// Created by ASUS on 2/1/2026.
//
#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

bool item_greater(item_t a, item_t b) {
    return a.key > b.key;
}

void swap(item_t* a, item_t* b) {
    item_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(heap_t* h, int i) {
    int largest = i;
    int l = LEFT(i);
    int r = RIGHT(i);

    if (l < h->size && item_greater(h->A[l], h->A[largest]))
        largest = l;
    if (r < h->size && item_greater(h->A[r], h->A[largest]))
        largest = r;

    if (largest != i) {
        swap(&h->A[i], &h->A[largest]);
        heapify(h, largest);
    }
}

void heap_build(heap_t* h) {
    for (int i = h->size / 2 - 1; i >= 0; i--) {
        heapify(h, i);
    }
}

heap_t* heap_create(int capacity) {
    heap_t* h = malloc(sizeof(heap_t));
    if (!h) return NULL;
    h->A = malloc(sizeof(item_t) * capacity);
    if (!h->A) {
        free(h);
        return NULL;
    }
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heap_destroy(heap_t* h) {
    if (h == NULL) return;
    free(h->A);
    free(h);
}

void heap_insert(heap_t* h, item_t x) {
    if (h->size == h->capacity) {
        fprintf(stderr, "Heap overflow\n");
        return;
    }

    int i = h->size;
    h->A[i] = x;
    h->size++;

    while (i > 0 && item_greater(h->A[i], h->A[PARENT(i)])) {
        swap(&h->A[i], &h->A[PARENT(i)]);
        i = PARENT(i);
    }
}

item_t heap_extract_max(heap_t* h) {
    item_t max = h->A[0];
    h->A[0] = h->A[h->size - 1];
    h->size--;
    heapify(h, 0);
    return max;
}

void heap_change_key(heap_t* h, int i, int new_key) {
    if (i < 0 || i >= h->size) {
        fprintf(stderr, "Index out of bounds for heap_change_key\n");
        return;
    }

    int old_key = h->A[i].key;
    h->A[i].key = new_key;

    if (new_key > old_key) {
        while (i > 0 && item_greater(h->A[i], h->A[PARENT(i)])) {
            swap(&h->A[i], &h->A[PARENT(i)]);
            i = PARENT(i);
        }
    } else {
        heapify(h, i);
    }
}

void print_heap_array(const heap_t* h) {
    for (int i = 0; i < h->size; i++)
        printf("{k:%d v:%d} ", h->A[i].key, h->A[i].value);
    printf("\n");
}
