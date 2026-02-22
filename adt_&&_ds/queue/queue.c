//
// Created by ASUS on 2/1/2026.
//

#include "queue.h"

#include <limits.h> // For INT_MIN
#include <stdio.h>
#include <stdlib.h>

queue_t* queue_create() {
    queue_t* q = (queue_t*) calloc(1, sizeof(queue_t));
    if (q == NULL) {
        fprintf(stderr, "Memory allocation failed for queue\n");
        return NULL;
    }
    return q;
}

void queue_enqueue(queue_t* q, int val) {
    if (q == NULL) {
        fprintf(stderr, "Queue pointer is NULL\n");
        return;
    }
    qnode_t* newNode = (qnode_t*) malloc(sizeof(qnode_t));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for queue node\n");
        return;
    }
    newNode->data = val;
    newNode->next = NULL;

    if (queue_is_empty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

qnode_t* queue_dequeue(queue_t* q) {
    if (q == NULL) {
        fprintf(stderr, "Queue pointer is NULL\n");
        return NULL;
    }
    if (queue_is_empty(q)) {
        fprintf(stderr, "Queue is empty, cannot dequeue\n");
        return NULL;
    }
    qnode_t* tmp = q->front;
    q->front = tmp->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    q->count--;
    tmp->next = NULL; // Detach node
    return tmp;
}

int queue_peek(const queue_t* q) {
    if (q == NULL) {
        fprintf(stderr, "Queue pointer is NULL\n");
        return INT_MIN;
    }
    if (queue_is_empty(q)) {
        fprintf(stderr, "Queue is empty\n");
        return INT_MIN;
    }
    return q->front->data;
}

bool queue_is_empty(const queue_t* q) {
    if (q == NULL) {
        return true;
    }
    return q->front == NULL;
}

bool queue_contains(const queue_t* q, int val) {
    if (q == NULL) {
        return false;
    }
    qnode_t* node = q->front;
    while (node != NULL) {
        if (node->data == val) {
            return true;
        }
        node = node->next;
    }
    return false;
}

int queue_size(const queue_t* q) {
    if (q == NULL) {
        return 0;
    }
    return q->count;
}

void queue_clear(queue_t* q) {
    if (q == NULL) {
        return;
    }
    qnode_t* node = q->front;
    while (node != NULL) {
        qnode_t* next = node->next;
        free(node);
        node = next;
    }
    q->front = q->rear = NULL;
    q->count = 0;
}

void queue_destroy(queue_t* q) {
    if (q == NULL) return;
    queue_clear(q);
    free(q);
}

void queue_print(const queue_t* q) {
    if (q == NULL) {
        printf("[Queue is NULL]\n");
        return;
    }
    printf("Front --->  ");
    qnode_t* node = q->front;
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL");
    printf("  <--- Rear\n");
}

int* queue_to_array(const queue_t* q) {
    if (q == NULL || queue_is_empty(q)) {
        return NULL;
    }
    int* arr = (int*) malloc(sizeof(int) * q->count);
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed for array\n");
        return NULL;
    }

    int i = 0;
    qnode_t* node = q->front;
    while (node != NULL) {
        arr[i++] = node->data;
        node = node->next;
    }
    return arr;
}
