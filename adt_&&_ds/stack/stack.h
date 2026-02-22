//
// Created by ASUS on 2/1/2026.
//

#ifndef ADS_BASICS_STACK_H
#define ADS_BASICS_STACK_H
#include <stdbool.h>

typedef struct knode_s {
    int data;
    struct knode_s* next;
} knode_t;

typedef struct {
    knode_t* head;
    int count;
} stack_t;


stack_t* stack_create();
void stack_destroy(stack_t* st);
void stack_push(stack_t* st, int value);
knode_t* stack_pop(stack_t* st);
int stack_peek(const stack_t* st);
bool stack_is_empty(const stack_t* st);
bool stack_contains(const stack_t* st, int value);
int stack_size(const stack_t* st);
void stack_print(const stack_t* st);
void stack_clear(stack_t* st);
int* stack_to_array(const stack_t* st);

#endif //ADS_BASICS_STACK_H