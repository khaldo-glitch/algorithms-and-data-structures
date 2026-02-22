//
// Created by ASUS on 2/4/2026.
//

#include "pq.h"

#include <stddef.h>

pq_t* pq_create(int capacity) {
    return heap_create(capacity);
}

void pq_destroy(pq_t* pq) {
    heap_destroy(pq);
}

void pq_insert(pq_t* pq, item_t x) {
    heap_insert(pq, x);
}

item_t pq_extract_max(pq_t* pq) {
    return heap_extract_max(pq);
}

item_t pq_peek(const pq_t* pq) {
    // The caller should ensure the PQ is not empty.
    return pq->A[0];
}

bool pq_is_empty(const pq_t* pq) {
    if (pq == NULL) return true;
    return pq->size == 0;
}

void pq_change_priority(pq_t* pq, int i, int new_priority) {
    // This is now a simple wrapper around the heap's core logic.
    heap_change_key(pq, i, new_priority);
}
