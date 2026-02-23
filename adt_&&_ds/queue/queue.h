#ifndef ADS_BASICS_QUEUE_H
#define ADS_BASICS_QUEUE_H
#include <stdbool.h>

typedef struct qnode_s {
    int data;
    struct qnode_s* next;
} qnode_t;

typedef struct {
    qnode_t* front;
    qnode_t* rear;
    int count;
} queue_t;

queue_t* queue_create();
void queue_destroy(queue_t* q);
void queue_enqueue(queue_t* q, int val);
qnode_t* queue_dequeue(queue_t* q);
int queue_peek(const queue_t* q);
bool queue_is_empty(const queue_t* q);
bool queue_contains(const queue_t* q, int val);
int queue_size(const queue_t* q);
void queue_clear(queue_t* q);
void queue_print(const queue_t* q);
int* queue_to_array(const queue_t* q);

#endif //ADS_BASICS_QUEUE_H