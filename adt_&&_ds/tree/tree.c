//
// Created by ASUS on 2/1/2026.
//

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

// ============================================================
// INTERNAL HELPERS
// ============================================================

// Helper for bst_to_sorted_array
static void inorder_fill_array(const btnode_t* root, int* arr, int* index) {
    if (root == NULL) return;
    inorder_fill_array(root->left, arr, index);
    arr[(*index)++] = root->key;
    inorder_fill_array(root->right, arr, index);
}

// ============================================================
// CREATION & DESTRUCTION
// ============================================================

btnode_t* btnode_create(int key) {
    btnode_t* n = (btnode_t*) malloc(sizeof(btnode_t));
    if (n == NULL) {
        fprintf(stderr, "Memory Allocation Error\n");
        return NULL;
    }
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}

btnode_t* btree_create_from_array(int* arr, int size) {
    btnode_t* root = NULL;
    for (int i = 0; i < size; i++) {
        root = bst_insert(root, arr[i]);
    }
    return root;
}

void btree_destroy(btnode_t* root) {
    if (root == NULL) return;
    btree_destroy(root->left);
    btree_destroy(root->right);
    free(root);
}

// ============================================================
// PROPERTIES
// ============================================================

int btree_count_nodes(const btnode_t* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + btree_count_nodes(root->left) + btree_count_nodes(root->right);
}

int btree_height(const btnode_t* root) {
    if (root == NULL) {
        return -1; // Height of empty tree is -1 (or 0 depending on definition)
    }
    int left = btree_height(root->left);
    int right = btree_height(root->right);

    return 1 + (left > right ? left : right);
}

// ============================================================
// TRAVERSALS
// ============================================================

void btree_preorder(const btnode_t* root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    btree_preorder(root->left);
    btree_preorder(root->right);
}

void btree_inorder(const btnode_t* root) {
    if (root == NULL) return;
    btree_inorder(root->left);
    printf("%d ", root->key);
    btree_inorder(root->right);
}

void btree_postorder(const btnode_t* root) {
    if (root == NULL) return;
    btree_postorder(root->left);
    btree_postorder(root->right);
    printf("%d ", root->key);
}

// ============================================================
// BINARY SEARCH TREE (BST) OPERATIONS
// ============================================================

btnode_t* bst_search(btnode_t* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (key < root->key)
        return bst_search(root->left, key);
    else if (key > root->key)
        return bst_search(root->right, key);

    return root; // Found
}

btnode_t* bst_min(btnode_t* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return bst_min(root->left);
}

btnode_t* bst_max(btnode_t* root) {
    if (root == NULL) return NULL;
    if (root->right == NULL) return root;
    return bst_max(root->right);
}

btnode_t* bst_insert(btnode_t* root, int key) {
    if (root == NULL) {
        return btnode_create(key);
    }
    if (key < root->key) {
        root->left = bst_insert(root->left, key);
    } else if (key > root->key) {
        root->right = bst_insert(root->right, key);
    }
    // If key == root->key, do nothing (no duplicates in this BST implementation)
    return root;
}

btnode_t* bst_remove(btnode_t* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key) {
        root->left = bst_remove(root->left, key);
    } else if (key > root->key) {
        root->right = bst_remove(root->right, key);
    } else {
        // Node found

        // Case 1: No child or One child
        if (root->left == NULL) {
            btnode_t* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            btnode_t* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Two children
        // Get the inorder successor (smallest in the right subtree)
        btnode_t* temp = bst_min(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = bst_remove(root->right, temp->key);
    }
    return root;
}

int* bst_to_sorted_array(const btnode_t* root, int* out_size) {
    if (root == NULL) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    int count = btree_count_nodes(root);
    int* arr = (int*) malloc(count * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed for array\n");
        return NULL;
    }

    int index = 0;
    inorder_fill_array(root, arr, &index);

    if (out_size) *out_size = count;
    return arr;
}
