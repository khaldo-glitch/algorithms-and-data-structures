//
// Created by ASUS on 2/1/2026.
//

#ifndef ADS_BASICS_HEAP_H
#define ADS_BASICS_HEAP_H

#include <stdbool.h>

#define PARENT(i) (((i)-1)/2)
#define LEFT(i)   (2*(i)+1)
#define RIGHT(i)  (2*(i)+2)

// Item for Heap and Priority Queue.
// `key` is used for priority, `value` stores the actual data (e.g., vertex ID).
typedef struct {
    int key;
    int value;
} item_t;

typedef struct heap_s {
    item_t* A;      // Array of items
    int size;       // Current number of items in the heap
    int capacity;   // Maximum number of items
} heap_t;

// --- Core Heap API ---
heap_t* heap_create(int capacity);
void heap_destroy(heap_t* h);
void heap_insert(heap_t* h, item_t x);
item_t heap_extract_max(heap_t* h);
void heap_change_key(heap_t* h, int i, int new_key);

// --- Helpers ---
void heapify(heap_t* h, int i);
void heap_build(heap_t* h);
void swap(item_t* a, item_t* b);
bool item_greater(item_t a, item_t b);
void print_heap_array(const heap_t* h);


#endif //ADS_BASICS_HEAP_H