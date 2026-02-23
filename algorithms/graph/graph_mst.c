#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "graph_algorithms.h"
#include "sorting.h"

// ============================================================
// Disjoint Set Union (DSU) - Simplified for Kruskal's
// ============================================================
typedef struct {
    int* parent;
} dsu_t;

static dsu_t* dsu_create(int n) {
    dsu_t* dsu = malloc(sizeof(dsu_t));
    dsu->parent = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dsu->parent[i] = i;
    return dsu;
}

static void dsu_destroy(dsu_t* dsu) {
    if (dsu) free(dsu->parent);
    free(dsu);
}

static int dsu_find(dsu_t* dsu, int i) {
    if (dsu->parent[i] == i) return i;
    return dsu->parent[i] = dsu_find(dsu, dsu->parent[i]); // Path Compression
}

static void dsu_union(dsu_t* dsu, int x, int y) {
    int rootX = dsu_find(dsu, x);
    int rootY = dsu_find(dsu, y);
    if (rootX != rootY) dsu->parent[rootX] = rootY;
}

// ============================================================
// Kruskal's Algorithm
// ============================================================

typedef struct { int u, v, weight; } sort_edge_t;

static void swap_edges(sort_edge_t* a, sort_edge_t* b) {
    sort_edge_t temp = *a; *a = *b; *b = temp;
}

static int partition_edges(sort_edge_t arr[], int left, int right) {
    int pivot_weight = arr[right].weight;
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j].weight < pivot_weight) {
            i++;
            swap_edges(&arr[i], &arr[j]);
        }
    }
    swap_edges(&arr[i + 1], &arr[right]);
    return (i + 1);
}

static void quick_sort_edges(sort_edge_t arr[], int left, int right) {
    if (left < right) {
        int p = partition_edges(arr, left, right);
        quick_sort_edges(arr, left, p - 1);
        quick_sort_edges(arr, p + 1, right);
    }
}

MSTResult* kruskal_mst(graph_t* g) {
    if (g == NULL) return NULL;

    int max_edges = 0;
    for (int i = 0; i < g->nv; i++)
        for (edge_t* e = g->adjList[i]; e != NULL; e = e->next)
            if (i < e->dest) max_edges++;

    sort_edge_t* all_edges = malloc(max_edges * sizeof(sort_edge_t));
    int k = 0;
    for (int i = 0; i < g->nv; i++)
        for (edge_t* e = g->adjList[i]; e != NULL; e = e->next)
            if (i < e->dest) all_edges[k++] = (sort_edge_t){i, e->dest, e->weight};

    quick_sort_edges(all_edges, 0, max_edges - 1);

    dsu_t* dsu = dsu_create(g->nv);
    MSTResult* result = malloc(sizeof(MSTResult));
    result->edges = malloc((g->nv - 1) * sizeof(mst_edge_t));
    result->num_edges = 0;
    result->total_weight = 0;

    for (int i = 0; i < max_edges; i++) {
        if (dsu_find(dsu, all_edges[i].u) != dsu_find(dsu, all_edges[i].v)) {
            result->edges[result->num_edges++] = (mst_edge_t){all_edges[i].u, all_edges[i].v, all_edges[i].weight};
            result->total_weight += all_edges[i].weight;
            dsu_union(dsu, all_edges[i].u, all_edges[i].v);
            if (result->num_edges == g->nv - 1) break;
        }
    }

    free(all_edges);
    dsu_destroy(dsu);
    return result;
}

// ============================================================
// Prim's Algorithm
// ============================================================

// Helper to find the unvisited vertex with the smallest key value.
static int find_min_key_vertex(int key[], bool inMST[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

MSTResult* prim_mst(graph_t* g, int start_node) {
    if (g == NULL || start_node < 0 || start_node >= g->nv) return NULL;

    int* parent = malloc(g->nv * sizeof(int));
    int* key = malloc(g->nv * sizeof(int));
    bool* inMST = malloc(g->nv * sizeof(bool));

    for (int i = 0; i < g->nv; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    key[start_node] = 0;

    for (int count = 0; count < g->nv; count++) {
        int u = find_min_key_vertex(key, inMST, g->nv);
        if (u == -1) break;

        inMST[u] = true;

        for (edge_t* e = g->adjList[u]; e != NULL; e = e->next) {
            int v = e->dest;
            if (!inMST[v] && e->weight < key[v]) {
                parent[v] = u;
                key[v] = e->weight;
            }
        }
    }

    MSTResult* result = malloc(sizeof(MSTResult));
    result->edges = malloc((g->nv - 1) * sizeof(mst_edge_t));
    result->num_edges = 0;
    result->total_weight = 0;

    for (int i = 0; i < g->nv; i++) {
        if (parent[i] != -1) {
            result->edges[result->num_edges++] = (mst_edge_t){parent[i], i, key[i]};
            result->total_weight += key[i];
        }
    }

    free(parent);
    free(key);
    free(inMST);
    return result;
}
