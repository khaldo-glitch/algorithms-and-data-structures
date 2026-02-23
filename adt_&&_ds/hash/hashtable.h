#ifndef ADS_BASICS_HASHTABLE_H
#define ADS_BASICS_HASHTABLE_H

#include <stddef.h>
#include <stdbool.h>
#include "slist.h" // Needed for Separate Chaining

// ============================================================
// PART 1: HASH FUNCTIONS (The "Receptionists")
// These are tools to convert a key into an array index.
// ============================================================

/**
 * @brief Hashes an integer key using the simple modulo method.
 * @param key The integer key to hash.
 * @param capacity The size of the hash table array.
 * @return An index in the range [0, capacity-1].
 */
size_t hash_int_modulo(int key, size_t capacity);

/**
 * @brief Hashes an integer key using the multiplication-modulo method.
 * Often provides better distribution than the simple modulo method.
 */
size_t hash_int_multiplication_mod(int key, size_t capacity);

/**
 * @brief Hashes a floating-point key.
 * One common method is to reinterpret the float's bits as an integer.
 */
size_t hash_float_multiplication(double s, double t,float key, size_t capacity);
/**
 * @brief Hashes a string key using Horner's method for polynomial rolling hash.
 * Good for general-purpose string hashing.
 */

size_t hash_short_str(const char* key, size_t capacity);

size_t hash_long_str_horner(const char* key, size_t capacity);


// ============================================================
// PART 2: SEPARATE CHAINING (The "Waiting List" Method)
// Collision Resolution by creating a linked list at each index.
// ============================================================



/**
 * @brief The main struct for a Separate Chaining hash table.
 * It is an array of pointers to singly-linked lists.
 */

/*
typedef struct {
    slist** table;      // Array of slist pointers (the "buckets").
    size_t capacity;    // Number of buckets in the array.
    size_t count;       // Total number of elements across all lists.
} ht_chaining_t;

// --- API for Separate Chaining ---

ht_chaining_t* ht_chaining_create(size_t capacity);
void ht_chaining_destroy(ht_chaining_t* ht);
void ht_chaining_insert(ht_chaining_t* ht, int key, int value); // For now, assumes int key/value
bool ht_chaining_search(const ht_chaining_t* ht, int key, int* out_value);
bool ht_chaining_delete(ht_chaining_t* ht, int key);
void ht_chaining_print(const ht_chaining_t* ht);


// ============================================================
// PART 3: OPEN ADDRESSING (The "Find Another Apartment" Method)
// Collision Resolution by finding the next empty slot in the array.
// ============================================================



*/


/**
 * @brief The state of a single slot in the Open Addressing table.
 */
typedef enum {
    SLOT_EMPTY,     // The slot has never been used.
    SLOT_OCCUPIED,  // The slot holds a valid element.
    SLOT_DELETED    // The slot once held an element that was deleted ("tombstone").
} slot_state_t;

/**
 * @brief A single entry (the "apartment") in the Open Addressing table.
 */

typedef struct {
    int key;
    int value;
    slot_state_t state;
} hash_entry_t;





/**
 * @brief The main struct for an Open Addressing hash table.
 * It is a single, large array of entries.
 */
/*
typedef struct {
    hash_entry_t* table; // The array of entries.
    size_t capacity;     // The total number of entries in the array.
    size_t count;        // Number of OCCUPIED slots.
} ht_open_t;

// --- API for Open Addressing ---

ht_open_t* ht_open_create(size_t capacity);
void ht_open_destroy(ht_open_t* ht);

// --- Main Operations with different Probing Strategies ---

// Linear Probing: Checks the next slot sequentially (i, i+1, i+2, ...).
void ht_open_insert_linear(ht_open_t* ht, int key, int value);
bool ht_open_search_linear(const ht_open_t* ht, int key, int* out_value);
bool ht_open_delete_linear(ht_open_t* ht, int key);

// Quadratic Probing: Checks slots in a quadratic sequence (i, i+1, i+4, i+9, ...).
void ht_open_insert_quadratic(ht_open_t* ht, int key, int value);
bool ht_open_search_quadratic(const ht_open_t* ht, int key, int* out_value);
bool ht_open_delete_quadratic(ht_open_t* ht, int key);

// Double Hashing: Uses a second hash function to determine the step size.
void ht_open_insert_double(ht_open_t* ht, int key, int value);
bool ht_open_search_double(const ht_open_t* ht, int key, int* out_value);
bool ht_open_delete_double(ht_open_t* ht, int key);

// --- Rehashing ---

/**
 * @brief Creates a new, larger table and moves all valid elements from the old one.
 * This is typically done when the load factor (count/capacity) gets too high.
 * @param old_ht The old hash table to rehash.
 * @return A new, larger hash table. The old one should be destroyed.
 */

/*

ht_open_t* ht_open_rehash(ht_open_t* old_ht);

void ht_open_print(const ht_open_t* ht);
*/


#endif //ADS_BASICS_HASHTABLE_H
