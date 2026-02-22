#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dp.h"

static int matrix_chain_min_cost(const int *dimensions, int matrix_count) {

    int n = matrix_count;

    int **cost_table = malloc((n + 1) * sizeof(int *));
    if (cost_table == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed for cost table rows.\n");
        return -1;
    }
    for (int i = 0; i <= n; i++) {
        cost_table[i] = malloc((n + 1) * sizeof(int));
        if (cost_table[i] == NULL) {
            fprintf(stderr, "ERROR: Memory allocation failed for cost table columns.\n");

            for (int j = 0; j < i; j++) free(cost_table[j]);
            free(cost_table);
            return -1;
        }
    }

    for (int i = 1; i <= n; i++) {
        cost_table[i][i] = 0;
    }

    for (int chain_length = 2; chain_length <= n; chain_length++) {
        for (int left = 1; left <= n - chain_length + 1; left++) {
            int right = left + chain_length - 1;
            cost_table[left][right] = INT_MAX;

            for (int split = left; split < right; split++) {

                int current_cost = cost_table[left][split] +
                                   cost_table[split + 1][right] +
                                   dimensions[left - 1] * dimensions[split] * dimensions[right];

                if (current_cost < cost_table[left][right]) {
                    cost_table[left][right] = current_cost;
                }
            }
        }
    }

    int result = cost_table[1][n];

    for (int i = 0; i <= n; i++) {
        free(cost_table[i]);
    }
    free(cost_table);

    return result;
}

static int *build_dimension_array(const matrix_t *matrix_list[], int matrix_count) {
    int *dimensions = malloc((matrix_count + 1) * sizeof(int));
    if (dimensions == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed for dimensions array.\n");
        return NULL;
    }

    dimensions[0] = matrix_list[0]->rows;
    for (int i = 0; i < matrix_count; i++) {

        if (i > 0 && matrix_list[i - 1]->cols != matrix_list[i]->rows) {
            fprintf(stderr, "ERROR: Incompatible matrix dimensions. A[%d] (%dx%d) and A[%d] (%dx%d).\n",
                    i - 1, matrix_list[i-1]->rows, matrix_list[i-1]->cols,
                    i, matrix_list[i]->rows, matrix_list[i]->cols);
            free(dimensions);
            return NULL;
        }
        dimensions[i + 1] = matrix_list[i]->cols;
    }

    return dimensions;
}

int minimum_matrix_mult_cost(const matrix_t *matrix_list[], int matrix_count) {
    if (matrix_list == NULL || matrix_count <= 0) {
        return 0;
    }
    if (matrix_count == 1) {
        return 0;
    }

    int *dimensions = build_dimension_array(matrix_list, matrix_count);
    if (dimensions == NULL) {
        return -1;
    }

    int result = matrix_chain_min_cost(dimensions, matrix_count);

    free(dimensions);
    return result;
}