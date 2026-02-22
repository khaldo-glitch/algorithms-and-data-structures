//
// Created by ASUS on 2/1/2026.
//
#include "hashtable.h"
#include <math.h>
#include <string.h>

#define PHI ((sqrt(5.0) - 1.0) / 2.0)  // GOLDEN RATIO FOR MULT METHOD

size_t hash_int_modulo(int key, size_t capacity) {
    return key % capacity;
}

size_t hash_int_multiplication_mod(int key, size_t capacity) {
    return ((size_t) floor(key*PHI)) % capacity;
}

size_t hash_float_multiplication(double s, double t,float key, size_t capacity) {
    return ((key-s)/(t-s))*capacity;
}

size_t hash_short_str(const char* key, size_t capacity) {
    const size_t b = 31;
    size_t hash = 0;
    size_t n = strlen(key);

    for (size_t i = 0; i < n; i++) {
        size_t power = 1;
        for (size_t j = 0; j < (n - 1 - i); j++) {
            power *= b;
        }
        hash += (unsigned char)key[i] * power;
    }
    return hash % capacity;
}


size_t hash_long_str_horner(const char* key, size_t capacity) {
    size_t hash = 0;
    size_t b = 127;
    for (size_t i = 0; key[i] != '\0'; i++) {
        hash = (hash * b + (unsigned char)key[i]) % capacity;
    }
    return hash;
}




























/*
// ============================================================
// HASH FUNCTIONS
// ============================================================

// Primary Hash Function
static size_t hash_primary(int key, size_t capacity) {
    // Simple modulo hashing. For negative keys, ensure positive result.
    return (size_t)((key % (int)capacity + capacity) % capacity);
}

// Secondary Hash Function (for Double Hashing)
// Must return non-zero and be relatively prime to capacity.
// A common choice is: prime - (key % prime)
static size_t hash_secondary(int key, size_t capacity) {
    size_t prime = capacity - 1; // Simplified assumption: capacity is prime-ish or we just pick smaller
    // Better: use a known prime smaller than capacity, e.g., 7 for small tables
    // For generic implementation, let's use: 1 + (key % (capacity - 1))
    if (capacity <= 1) return 1;
    return 1 + (size_t)((key % (int)(capacity - 1) + (capacity - 1)) % (capacity - 1));
}

// ============================================================
// CREATION & DESTRUCTION
// ============================================================

hashtable_t* hashtable_create(size_t capacity, probing_type_t type) {
    hashtable_t* ht = (hashtable_t*) malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        fprintf(stderr, "Memory allocation failed for hash table struct\n");
        return NULL;
    }

    ht->table = (hash_entry_t*) malloc(sizeof(hash_entry_t) * capacity);
    if (ht->table == NULL) {
        fprintf(stderr, "Memory allocation failed for hash table array\n");
        free(ht);
        return NULL;
    }

    // Initialize all slots as EMPTY
    for (size_t i = 0; i < capacity; i++) {
        ht->table[i].state = SLOT_EMPTY;
    }

    ht->capacity = capacity;
    ht->count = 0;
    ht->probing_type = type;

    return ht;
}

void hashtable_destroy(hashtable_t* ht) {
    if (ht == NULL) return;
    free(ht->table);
    free(ht);
}

// ============================================================
// OPERATIONS
// ============================================================

bool hashtable_insert(hashtable_t* ht, int key, int value) {
    if (ht == NULL) return false;
    if (ht->count == ht->capacity) {
        fprintf(stderr, "Hash table is full\n");
        return false;
    }

    size_t index = hash_primary(key, ht->capacity);
    size_t start_index = index;
    size_t i = 0; // Probe step

    while (ht->table[index].state == SLOT_OCCUPIED) {
        // If key already exists, update value
        if (ht->table[index].key == key) {
            ht->table[index].value = value;
            return true;
        }

        i++;
        if (ht->probing_type == PROBING_LINEAR) {
            index = (start_index + i) % ht->capacity;
        } else if (ht->probing_type == PROBING_QUADRATIC) {
            index = (start_index + i * i) % ht->capacity;
        } else if (ht->probing_type == PROBING_DOUBLE) {
            size_t step = hash_secondary(key, ht->capacity);
            index = (start_index + i * step) % ht->capacity;
        }

        // Safety break to prevent infinite loops if table is full or probing fails to cover all slots
        if (i >= ht->capacity) return false;
    }

    // Found an EMPTY or DELETED slot
    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].state = SLOT_OCCUPIED;
    ht->count++;
    return true;
}

bool hashtable_search(const hashtable_t* ht, int key, int* out_value) {
    if (ht == NULL) return false;

    size_t index = hash_primary(key, ht->capacity);
    size_t start_index = index;
    size_t i = 0;

    while (ht->table[index].state != SLOT_EMPTY) {
        if (ht->table[index].state == SLOT_OCCUPIED && ht->table[index].key == key) {
            if (out_value) *out_value = ht->table[index].value;
            return true;
        }

        i++;
        if (ht->probing_type == PROBING_LINEAR) {
            index = (start_index + i) % ht->capacity;
        } else if (ht->probing_type == PROBING_QUADRATIC) {
            index = (start_index + i * i) % ht->capacity;
        } else if (ht->probing_type == PROBING_DOUBLE) {
            size_t step = hash_secondary(key, ht->capacity);
            index = (start_index + i * step) % ht->capacity;
        }

        if (i >= ht->capacity) return false;
    }

    return false;
}

bool hashtable_delete(hashtable_t* ht, int key) {
    if (ht == NULL) return false;

    size_t index = hash_primary(key, ht->capacity);
    size_t start_index = index;
    size_t i = 0;

    while (ht->table[index].state != SLOT_EMPTY) {
        if (ht->table[index].state == SLOT_OCCUPIED && ht->table[index].key == key) {
            ht->table[index].state = SLOT_DELETED; // Mark as tombstone
            ht->count--;
            return true;
        }

        i++;
        if (ht->probing_type == PROBING_LINEAR) {
            index = (start_index + i) % ht->capacity;
        } else if (ht->probing_type == PROBING_QUADRATIC) {
            index = (start_index + i * i) % ht->capacity;
        } else if (ht->probing_type == PROBING_DOUBLE) {
            size_t step = hash_secondary(key, ht->capacity);
            index = (start_index + i * step) % ht->capacity;
        }

        if (i >= ht->capacity) return false;
    }

    return false;
}

void hashtable_print(const hashtable_t* ht) {
    if (ht == NULL) return;
    printf("Hash Table (Size: %zu, Count: %zu)\n", ht->capacity, ht->count);
    for (size_t i = 0; i < ht->capacity; i++) {
        printf("[%zu]: ", i);
        if (ht->table[i].state == SLOT_OCCUPIED) {
            printf("{%d : %d}", ht->table[i].key, ht->table[i].value);
        } else if (ht->table[i].state == SLOT_DELETED) {
            printf("DELETED");
        } else {
            printf("EMPTY");
        }
        printf("\n");
    }
}

double hashtable_load_factor(const hashtable_t* ht) {
    if (ht == NULL || ht->capacity == 0) return 0.0;
    return (double)ht->count / (double)ht->capacity;
}
*/