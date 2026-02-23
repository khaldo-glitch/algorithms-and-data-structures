#ifndef ADS_BASICS_RECURSION_H
#define ADS_BASICS_RECURSION_H
#include "slist.h"

// ============================================================
// BASIC RECURSION
// ============================================================

long long factorial(int n);
long long fibonacci(int n);

snode_t* list_find_rec(slist* l, int val);
snode_t* list_find_node_rec(snode_t* node, int val);

// ============================================================
// TAIL RECURSION
// ============================================================

long long factorial_tail(int n);
long long factorial_tail_helper(int n, long long accumulator);

// ============================================================
// COMBINATORICS
// ============================================================

typedef struct {
    char letter;
} item_t;

/**
 * Arrangements with Repetition (n^k)
 * Order matters, repetition allowed.
 * Example: {a, b}, k=2 -> {a,a}, {a,b}, {b,a}, {b,b}
 */
void arrangements_rep(item_t* val, item_t* sol, int n, int k, int pos, int* count);

/**
 * Simple Arrangements (nPk)
 * Order matters, NO repetition.
 * Example: {a, b, c}, k=2 -> {a,b}, {a,c}, {b,a}, {b,c}, {c,a}, {c,b}
 */
void simple_arrangements(item_t* val, item_t* sol, int n, int k, int pos, int* count, int* marked);

/**
 * Simple Permutations (nPn)
 * Order matters, NO repetition, using ALL items.
 * Example: {a, b} -> {a,b}, {b,a}
 */
void simple_permutations(item_t* val, item_t* sol, int n, int pos, int* count, int* marked);

/**
 * Permutations with Repetition (Multiset Permutation)
 * Order .matters, using all items with specific frequencies.
 * Example: {a:2, b:1} -> {a,a,b}, {a,b,a}, {b,a,a}
 * @param freq Array where freq[i] is the count of item val[i]
 */
void permutations_rep(item_t* val, item_t* sol, int n_total, int n_distinct, int pos, int* count, int* freq);

/**
 * Simple Combinations (nCk)
 * Order DOES NOT matter, NO repetition.
 * Example: {a, b, c}, k=2 -> {a,b}, {a,c}, {b,c}
 */
void simple_combinations(item_t* val, item_t* sol, int n, int k, int pos, int* count, int start);

/**
 * Combinations with Repetition
 * Order DOES NOT matter, repetition allowed.
 * Example: {a, b}, k=2 -> {a,a}, {a,b}, {b,b}
 */
void combinations_rep(item_t* val, item_t* sol, int n, int k, int pos, int* count, int start);


//////////////////////////////////////////////////////
typedef  struct val_s {
    int num_choices;
    int* choices;
}multi_pr_val_t;

void  mult_princ(multi_pr_val_t* val, int* sol, int n, int pos, int* count);

/////////////////////////////////////////////////////

#endif //ADS_BASICS_RECURSION_H