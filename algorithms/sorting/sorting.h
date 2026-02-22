//
// Created by ASUS on 2/1/2026.
//

#ifndef ADS_BASICS_SORTING_H
#define ADS_BASICS_SORTING_H

#include "heap.h" // For item_t used in heap_sort

void merge_sort(int arr[], int left, int right);
void quick_sort(int arr[], int left, int right);

// Note: heap_sort sorts an array of item_t structs, not simple integers.
void heap_sort(item_t* A, int n);

#endif //ADS_BASICS_SORTING_H