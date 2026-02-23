#include <stdio.h>
#include "dlist.h"
#include <stdlib.h>

dlist* dlist_create() {
    dlist* l = (dlist*) malloc(sizeof(dlist));
    if (l == NULL) {
        fprintf(stderr, "Memory allocation failed for list\n");
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void dlist_destroy(dlist* l) {
    if (l == NULL) {
        fprintf(stderr, "Double-Linked List Pointer is NULL\n");
        return;
    }
    dnode_t* node = l->head;
    while (node != NULL) {
        dnode_t* next = node->next;
        free(node);
        node = next;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    free(l);
}

void dlist_insert_head(dlist* l, int value) {
    if (l == NULL) return;

    dnode_t* node = (dnode_t*) malloc(sizeof(dnode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data = value;
    node->prev = NULL;
    node->next = l->head;

    if (l->head != NULL) {
        l->head->prev = node;
    }
    l->head = node;

    // If list was empty, head is also tail
    if (l->tail == NULL) {
        l->tail = node;
    }
    l->size++;
}

void dlist_insert_tail(dlist* l, int value) {
    if (l == NULL) return;

    dnode_t* node = (dnode_t*) malloc(sizeof(dnode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data = value;
    node->next = NULL;
    node->prev = l->tail;

    if (l->tail != NULL) {
        l->tail->next = node;
    } else {
        l->head = node; // List was empty
    }
    l->tail = node;
    l->size++;
}

void dlist_insert_after(dlist* l, dnode_t* pos, int value) {
    if (l == NULL || pos == NULL) return;

    dnode_t* node = (dnode_t*) malloc(sizeof(dnode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data = value;
    node->prev = pos;
    node->next = pos->next;

    if (pos->next != NULL) {
        pos->next->prev = node;
    } else {
        l->tail = node; // pos was the tail, so new node is now tail
    }
    pos->next = node;
    l->size++;
}

void dlist_insert_before(dlist* l, dnode_t* pos, int value) {
    if (l == NULL || pos == NULL) return;

    // Edge Case: Inserting before the head is just insert_head
    if (pos == l->head) {
        dlist_insert_head(l, value);
        return;
    }

    dnode_t* node = (dnode_t*) malloc(sizeof(dnode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data = value;

    // Wire up the new node
    node->next = pos;
    node->prev = pos->prev;

    // Update surrounding nodes
    if (pos->prev != NULL) {
        pos->prev->next = node;
    }
    pos->prev = node;

    l->size++;
}

dnode_t* dlist_find(const dlist* l, int value) {
    if (l == NULL) return NULL;
    dnode_t* node = l->head;
    while (node != NULL) {
        if (node->data == value) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void dlist_print(const dlist* l) {
    if (l == NULL) {
        printf("[List is NULL]\n");
        return;
    }

    printf("D-List (size=%zu): NULL <- ", l->size);
    dnode_t* node = l->head;
    while (node != NULL) {
        printf("%d ", node->data);
        if (node->next != NULL) printf("<=> ");
        else printf("-> ");
        node = node->next;
    }
    printf("NULL\n");
}

void dlist_delete_head(dlist* l) {
    if (l == NULL || l->head == NULL) return;

    dnode_t* tmp = l->head;
    l->head = l->head->next;

    if (l->head == NULL) {
        l->tail = NULL;
    } else {
        l->head->prev = NULL;
    }

    free(tmp);
    l->size--;
}

void dlist_delete_tail(dlist* l) {
    if (l == NULL || l->head == NULL) return;

    dnode_t* tmp = l->tail;

    if (l->head == l->tail) {
        l->head = NULL;
        l->tail = NULL;
    } else {
        l->tail = l->tail->prev;
        l->tail->next = NULL;
    }

    free(tmp);
    l->size--;
}

void dlist_delete_node(dlist* l, dnode_t* node) {
    if (l == NULL || node == NULL) return;

    if (node == l->head) {
        dlist_delete_head(l);
        return;
    }

    if (node == l->tail) {
        dlist_delete_tail(l);
        return;
    }

    // Middle deletion
    dnode_t* prev_node = node->prev;
    dnode_t* next_node = node->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    free(node);
    l->size--;
}

void dlist_delete_byValue(dlist* l, int value) {
    if (l == NULL || l->head == NULL) return;

    dnode_t* node = dlist_find(l, value);
    if (node != NULL) {
        dlist_delete_node(l, node);
    }
}
