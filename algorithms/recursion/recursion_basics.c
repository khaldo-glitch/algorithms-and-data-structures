#include <stdint.h>
#include <stdio.h>

#include "recursion.h"

//////////////////////////////////////////////////////////////////
////// BASIC RECURSION FUNCTIONS
/////////////////////////////////////////////////////////////////

long long factorial(int n) {
    if (n < 0) return -1;
    if (n == 0 || n == 1)
        return 1;
    if (n == 2)
        return 2;
    return n * factorial(n - 1);
}

snode_t* list_find_rec(slist* l, int val) {
    if (l == NULL) return NULL;
    return list_find_node_rec(l->head, val);
}

snode_t* list_find_node_rec(snode_t* node, int val) {
    // Base case: End of list or empty list
    if (node == NULL) {
        fprintf(stderr, "Value %d not found\n", val);
        return NULL;
    }

    // Base case: Found
    if (node->data == val) {
        return node;
    }

    // Recursive step
    return list_find_node_rec(node->next, val);
}


long long fibonacci(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/////////////////////////////////////////////////////////////////
//// TAIL RECURSION
////////////////////////////////////////////////////////////////


long long factorial_tail(int n) {
    if (n < 0) return -1;
    return factorial_tail_helper(n, 1);
}

long long factorial_tail_helper(int n, long long accumulator) {
    if (n == 0)
        return accumulator;
    return factorial_tail_helper(n - 1, accumulator * n);
}
