#include "recursion.h"
#include <stdio.h>

// Helper to display a single solution set
void display_solution(item_t * arr, int n, int* count) {
    printf("Set No.%d: {", *count + 1); // 1-based indexing
    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            printf("%c, ", arr[i].letter);
        else
            printf("%c", arr[i].letter);
    }
    printf("}\n");
}

// ============================================================
// ARRANGEMENTS
// ============================================================

// Arrangements with Repetition (n^k)
// Example: {a, b}, k=2 -> {a,a}, {a,b}, {b,a}, {b,b}
void arrangements_rep(item_t* val, item_t* sol, int n, int k, int pos, int* count) {
    if (pos >= k) {
        display_solution(sol, k, count);
        (*count)++;
        return;
    }
    for (int i = 0; i < n; i++) {
        sol[pos] = val[i];
        arrangements_rep(val, sol, n, k, pos + 1, count);
    }
}

// Simple Arrangements (nPk)
// Example: {a, b, c}, k=2 -> {a,b}, {a,c}, {b,a}, {b,c}, {c,a}, {c,b}
void simple_arrangements(item_t* val, item_t* sol, int n, int k, int pos, int* count, int* marked) {
    if (pos >= k) {
        display_solution(sol, k, count);
        (*count)++;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (marked[i] == 0) {
            marked[i] = 1;

            sol[pos] = val[i];
            simple_arrangements(val, sol, n, k, pos + 1, count, marked);

            marked[i] = 0; // Backtrack
        }
    }
}

// ============================================================
// PERMUTATIONS
// ============================================================

// Simple Permutations (nPn)
// Example: {a, b} -> {a,b}, {b,a}
void simple_permutations(item_t* val, item_t* sol, int n, int pos, int* count, int* marked) {
    if (pos >= n) {
        display_solution(sol, n, count);
        (*count)++;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (marked[i] == 0) {
            marked[i] = 1;

            sol[pos] = val[i];
            simple_permutations(val, sol, n, pos + 1, count, marked);

            marked[i] = 0; // Backtrack
        }
    }
}

// Permutations with Repetition (Multiset)
// Example: {a:2, b:1} -> {a,a,b}, {a,b,a}, {b,a,a}
void permutations_rep(item_t* val, item_t* sol, int n_total, int n_distinct, int pos, int* count, int* freq) {
    if (pos >= n_total) {
        display_solution(sol, n_total, count);
        (*count)++;
        return;
    }

    for (int i = 0; i < n_distinct; i++) {
        if (freq[i] > 0) {
            freq[i]--; // Use one instance of item i

            sol[pos] = val[i];
            permutations_rep(val, sol, n_total, n_distinct, pos + 1, count, freq);

            freq[i]++; // Backtrack
        }
    }
}

// ============================================================
// COMBINATIONS
// ============================================================

// Simple Combinations (nCk)
// Example: {a, b, c}, k=2 -> {a,b}, {a,c}, {b,c}
void simple_combinations(item_t* val, item_t* sol, int n, int k, int pos, int* count, int start) {
    if (pos >= k) {
        display_solution(sol, k, count);
        (*count)++;
        return;
    }
    for (int i = start; i < n; i++) {
        sol[pos] = val[i];
        simple_combinations(val, sol, n, k, pos + 1, count, i + 1);
    }
}

// Combinations with Repetition
// Example: {a, b}, k=2 -> {a,a}, {a,b}, {b,b}
void combinations_rep(item_t* val, item_t* sol, int n, int k, int pos, int* count, int start) {
    if (pos >= k) {
        display_solution(sol, k, count);
        (*count)++;
        return;
    }
    for (int i = start; i < n; i++) {
        sol[pos] = val[i];
        // i ensures we can pick the same element again, but never an earlier one (no order)
        combinations_rep(val, sol, n, k, pos + 1, count, i);
    }
}



void mult_princ(multi_pr_val_t* val, int* sol, int n, int pos, int* count) {
    if (pos >= n) {
        (*count)++;
        return;
    }
    for (int i = 0; i < val[pos].num_choices; i++) {
        sol[pos] = val[pos].choices[i];
        mult_princ(val, sol, n, pos + 1, count);
    }
}
