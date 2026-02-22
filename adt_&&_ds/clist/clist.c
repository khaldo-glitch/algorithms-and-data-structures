//
// Created by ASUS on 2/1/2026.
//

#include <stdio.h>
#include "clist.h"
#include <stdlib.h>

clist* clist_create() {
    clist* l = (clist*) malloc(sizeof(clist));
    if (l == NULL) {
        fprintf(stderr, "Memory allocation failed for list\n");
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void clist_destroy(clist* l) {
    if (l == NULL) return;

    if (l->head != NULL) {
        cnode_t* node = l->head;
        // Break the circle to allow standard traversal destruction
        // or just iterate using size/do-while
        do {
            cnode_t* next = node->next;
            free(node);
            node = next;
        } while (node != l->head);
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    free(l);
}

void clist_insert_head(clist* l, int value) {
    if (l == NULL) return;

    cnode_t* node = (cnode_t*) malloc(sizeof(cnode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data = value;

    if (l->head == NULL) {
        // Empty list: point to itself
        l->head = node;
        l->tail = node;
        node->next = node;
    } else {
        node->next = l->head;
        l->head = node;
        l->tail->next = l->head; // Maintain the cycle
    }
    l->size++;
}

void clist_insert_tail(clist* l, int value) {
    if (l == NULL) return;

    if (l->head == NULL) {
        clist_insert_head(l, value); // Logic is identical for empty list
        return;
    }

    cnode_t* node = (cnode_t*) malloc(sizeof(cnode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data = value;

    node->next = l->head; // New tail points to head
    l->tail->next = node; // Old tail points to new tail
    l->tail = node;       // Update tail pointer
    l->size++;
}

void clist_insert_after(clist* l, cnode_t* pos, int value) {
    if (l == NULL || pos == NULL) return;

    cnode_t* node = (cnode_t*) malloc(sizeof(cnode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data = value;

    node->next = pos->next;
    pos->next = node;

    // If we inserted after the tail, the new node becomes the tail
    if (pos == l->tail) {
        l->tail = node;
    }
    l->size++;
}

cnode_t* clist_find(const clist* l, int value) {
    if (l == NULL || l->head == NULL) return NULL;

    cnode_t* node = l->head;
    do {
        if (node->data == value) {
            return node;
        }
        node = node->next;
    } while (node != l->head); // Stop when we wrap around

    return NULL;
}

cnode_t* clist_find_parent(const clist* l, int value) {
    if (l == NULL || l->head == NULL) return NULL;

    cnode_t* node = l->head;

    // Check if head is the target, parent would be tail
    if (l->head->data == value) {
        return l->tail;
    }

    do {
        if (node->next->data == value) {
            return node;
        }
        node = node->next;
    } while (node != l->head);

    return NULL;
}

void clist_delete_head(clist* l) {
    if (l == NULL || l->head == NULL) return;

    cnode_t* tmp = l->head;

    if (l->head == l->tail) {
        // Only one node exists
        l->head = NULL;
        l->tail = NULL;
    } else {
        l->head = l->head->next; // Move head forward
        l->tail->next = l->head; // Update tail to point to new head
    }

    free(tmp);
    l->size--;
}

void clist_delete_tail(clist* l) {
    if (l == NULL || l->head == NULL) return;

    if (l->head == l->tail) {
        clist_delete_head(l);
        return;
    }

    // Since it's singly linked, we must traverse to find the node before tail
    cnode_t* node = l->head;
    while (node->next != l->tail) {
        node = node->next;
    }

    // 'node' is now the new tail
    cnode_t* old_tail = l->tail;

    l->tail = node;
    l->tail->next = l->head; // Close the loop

    free(old_tail);
    l->size--;
}

void clist_delete_after(clist* l, cnode_t* pos) {
    if (l == NULL || pos == NULL) return;

    // In a circular list, pos->next is never NULL unless the list is somehow broken,
    // but if the list has only 1 element, pos->next is pos itself.
    if (pos->next == pos) {
        // Deleting the only node (which is after itself in a loop)
        clist_delete_head(l);
        return;
    }

    cnode_t* tmp = pos->next;

    // If we are deleting the head (which is 'after' the tail)
    if (tmp == l->head) {
        l->head = tmp->next;
        l->tail->next = l->head; // Ensure tail points to new head
    }

    // If we are deleting the tail
    if (tmp == l->tail) {
        l->tail = pos;
    }

    pos->next = tmp->next;
    free(tmp);
    l->size--;
}

void clist_delete_byValue(clist* l, int value) {
    if (l == NULL || l->head == NULL) return;

    // Special Case: Deleting Head
    if (l->head->data == value) {
        clist_delete_head(l);
        return;
    }

    // Find the node BEFORE the target value
    cnode_t* parent = clist_find_parent(l, value);
    if (parent != NULL) {
        clist_delete_after(l, parent);
    }
}

void clist_print(const clist* l) {
    if (l == NULL) {
        printf("[List is NULL]\n");
        return;
    }
    if (l->head == NULL) {
        printf("C-List (size=0): [Empty]\n");
        return;
    }

    printf("C-List (size=%zu): ", l->size);
    cnode_t* node = l->head;
    do {
        printf("%d -> ", node->data);
        node = node->next;
    } while (node != l->head);

    printf("(back to head)\n");
}
