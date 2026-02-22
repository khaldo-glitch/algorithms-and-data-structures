#include "sorting.h"
#include <stdio.h> // For potential debugging or NULL if needed

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int l[n1], r[n2];

    for (i = 0; i < n1; i++) {
        l[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        r[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (l[i] <= r[j]) {
            arr[k] = l[i];
            i++;
        } else {
            arr[k] = r[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = l[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = r[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}