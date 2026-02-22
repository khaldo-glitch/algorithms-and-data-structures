//
// Created by ASUS on 2/4/2026.
//

#ifndef ADS_BASICS_PQ_H
#define ADS_BASICS_PQ_H

#include "heap.h"

// A Priority Queue is implemented as a wrapper around a Heap.
typedef heap_t pq_t;

pq_t* pq_create(int capacity);
void pq_destroy(pq_t* pq);

// Inserts an item into the priority queue.
void pq_insert(pq_t* pq, item_t x);

// Removes and returns the item with the highest priority (max key).
item_t pq_extract_max(pq_t* pq);

// Returns the item with the highest priority without removing it.
// NOTE: Behavior is undefined if the queue is empty.
item_t pq_peek(const pq_t* pq);

// Checks if the priority queue is empty.
bool pq_is_empty(const pq_t* pq);

// Changes the priority (key) of an item at a specific index.
void pq_change_priority(pq_t* pq, int i, int new_priority);

#endif //ADS_BASICS_PQ_H