//
// Created by ASUS on 2/1/2026.
//
#include "stack.h"

#include <limits.h> // For INT_MIN
#include <stdio.h>
#include <stdlib.h>

stack_t* stack_create() {
    stack_t* st = (stack_t*) malloc(sizeof(stack_t));
    if (st == NULL) {
        fprintf(stderr, "Memory allocation failed for stack\n");
        return NULL;
    }
    st->head = NULL;
    st->count = 0;
    return st;
}

void stack_push(stack_t* st, int value) {
    if (st == NULL) {
        fprintf(stderr, "Stack pointer is NULL\n");
        return;
    }
    knode_t* newNode = (knode_t*) malloc(sizeof(knode_t));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for stack node\n");
        return;
    }

    newNode->data = value;
    newNode->next = st->head;
    st->head = newNode;
    st->count++;
}

knode_t* stack_pop(stack_t* st) {
    if (st == NULL) {
        fprintf(stderr, "Stack pointer is NULL\n");
        return NULL;
    }
    if (stack_is_empty(st)) {
        fprintf(stderr, "Stack is empty, cannot pop\n");
        return NULL;
    }
    knode_t* tmp = st->head;
    st->head = tmp->next;
    st->count--;

    tmp->next = NULL; // Detach the node from the stack
    return tmp;
}

int stack_peek(const stack_t* st) {
    if (st == NULL) {
        fprintf(stderr, "Stack pointer is NULL\n");
        return INT_MIN;
    }
    if (stack_is_empty(st)) {
        fprintf(stderr, "Stack is empty\n");
        return INT_MIN;
    }
    return st->head->data;
}

bool stack_is_empty(const stack_t* st) {
    if (st == NULL) {
        return true; // Treat NULL stack as empty
    }
    return st->head == NULL;
}

bool stack_contains(const stack_t* st, int value) {
    if (st == NULL) {
        return false;
    }
    knode_t* node = st->head;
    while (node != NULL) {
        if (node->data == value)
            return true;
        node = node->next;
    }
    return false;
}

int stack_size(const stack_t* st) {
    if (st == NULL) {
        return 0; // Treat NULL stack as size 0
    }
    return st->count;
}

void stack_print(const stack_t* st) {
    if (st == NULL) {
        printf("[Stack is NULL]\n");
        return;
    }
    printf("Top ---> ");
    knode_t* node = st->head;
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void stack_clear(stack_t* st) {
    if (st == NULL) {
        return;
    }
    knode_t* node = st->head;
    while (node != NULL) {
        knode_t* next = node->next;
        free(node);
        node = next;
    }
    st->head = NULL;
    st->count = 0;
}

void stack_destroy(stack_t* st) {
    if (st == NULL) return;
    stack_clear(st);
    free(st);
}

int* stack_to_array(const stack_t* st) {
    if (st == NULL || stack_is_empty(st)) {
        return NULL;
    }
    int* arr = (int*) malloc(sizeof(int) * st->count);
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed for array\n");
        return NULL;
    }

    int i = 0;
    knode_t* node = st->head;
    while (node != NULL) {
        arr[i++] = node->data;
        node = node->next;
    }
    return arr;
}
