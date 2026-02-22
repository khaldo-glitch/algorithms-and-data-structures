//
// Created by ASUS on 2/1/2026.
//

#ifndef ADS_BASICS_TREE_H
#define ADS_BASICS_TREE_H

#include <stddef.h> // For size_t

// Binary Tree Node
typedef struct btnode_s {
    int key;
    struct btnode_s* left;
    struct btnode_s* right;
} btnode_t;

// ============================================================
// CREATION & DESTRUCTION
// ============================================================

// Creates a single node with the given key
btnode_t* btnode_create(int key);

// Creates a BST from an array of integers
btnode_t* btree_create_from_array(int* arr, int size);

// Destroys the entire tree (frees all nodes)
void btree_destroy(btnode_t* root);

// ============================================================
// PROPERTIES
// ============================================================

int btree_count_nodes(const btnode_t* root);
int btree_height(const btnode_t* root);

// ============================================================
// TRAVERSALS
// ============================================================

void btree_preorder(const btnode_t* root);
void btree_inorder(const btnode_t* root);
void btree_postorder(const btnode_t* root);

// ============================================================
// BINARY SEARCH TREE (BST) OPERATIONS
// ============================================================

btnode_t* bst_insert(btnode_t* root, int key);
btnode_t* bst_remove(btnode_t* root, int key);
btnode_t* bst_search(btnode_t* root, int key);
btnode_t* bst_min(btnode_t* root);
btnode_t* bst_max(btnode_t* root);

// Converts a BST to a sorted array (using in-order traversal)
// Returns a dynamically allocated array (caller must free)
int* bst_to_sorted_array(const btnode_t* root, int* out_size);

#endif //ADS_BASICS_TREE_H