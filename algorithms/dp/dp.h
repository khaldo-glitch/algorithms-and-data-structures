//
// Created by ASUS on 2/1/2026.
//

#ifndef ADS_BASICS_ALGORITHMS_DP_DP_H
#define ADS_BASICS_ALGORITHMS_DP_DP_H

typedef struct {
    int **data;
    int rows;
    int cols;
} matrix_t;

int minimum_matrix_mult_cost(const matrix_t *matrix_list[], int matrix_count);

#endif //ADS_BASICS_ALGORITHMS_DP_DP_H