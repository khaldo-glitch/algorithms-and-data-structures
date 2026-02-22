#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "graph_algorithms.h"
#include "pq.h" // For Prim's Algorithm

// ============================================================
// Disjoint Set Union (DSU) / Union-Find for Kruskal's
// ============================================================
typedef struct {
    int* parent;
    int* rank; // Added for Union by Rank optimization
} dsu_t;

static dsu_t* dsu_create(int n) {
    dsu_t* dsu = malloc(sizeof(dsu_t));
    dsu->parent = malloc(n * sizeof(int));
    dsu->rank = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i; // Each element is its own parent initially
        dsu->rank[i] = 0;   // Initial rank is 0
    }
    return dsu;
}

static void dsu_destroy(dsu_t* dsu) {
    if (dsu == NULL) return;
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

// Find the representative (root) of the set containing i
static int dsu_find(dsu_t* dsu, int i) {
    if (dsu->parent[i] == i)
        return i;
    // Path compression for optimization
    return dsu->parent[i] = dsu_find(dsu, dsu->parent[i]);
}

// Union of two sets (Optimized with Union by Rank)
static void dsu_union(dsu_t* dsu, int x, int y) {
    int rootX = dsu_find(dsu, x);
    int rootY = dsu_find(dsu, y);
    if (rootX != rootY) {
        if (dsu->rank[rootX] < dsu->rank[rootY]) {
            dsu->parent[rootX] = rootY;
        } else if (dsu->rank[rootX] > dsu->rank[rootY]) {
            dsu->parent[rootY] = rootX;
        } else {
            dsu->parent[rootY] = rootX;
            dsu->rank[rootX]++;
        }
    }
}

// ============================================================
// Kruskal's Algorithm
// ============================================================

// Temporary struct to keep edge properties linked during sort
typedef struct {
    int u;
    int v;
    int weight;
} sort_edge_t;

// Helper to compare sort_edge_t for qsort
static int compare_sort_edges(const void* a, const void* b) {
    sort_edge_t* edgeA = (sort_edge_t*)a;
    sort_edge_t* edgeB = (sort_edge_t*)b;
    return edgeA->weight - edgeB->weight;
}

MSTResult* kruskal_mst(graph_t* g) {
    if (g == NULL) return NULL;

    // 1. Count unique edges (assuming undirected graph)
    int max_edges = 0;
    for (int i = 0; i < g->nv; i++) {
        for (edge_t* e = g->adjList[i]; e != NULL; e = e->next) {
            // Only count if i < e->dest to avoid duplicate edges in undirected graphs
            if (i < e->dest) {
                max_edges++;
            }
        }
    }

    // 2. Populate edge array for sorting
    sort_edge_t* all_edges = malloc(max_edges * sizeof(sort_edge_t));
    int k = 0;
    for (int i = 0; i < g->nv; i++) {
        for (edge_t* e = g->adjList[i]; e != NULL; e = e->next) {
            if (i < e->dest) {
                all_edges[k].u = i;
                all_edges[k].v = e->dest;
                all_edges[k].weight = e->weight;
                k++;
            }
        }
    }

    // 3. Sort all edges by weight
    qsort(all_edges, max_edges, sizeof(sort_edge_t), compare_sort_edges);

    // 4. Initialize DSU and MST result
    dsu_t* dsu = dsu_create(g->nv);
    MSTResult* result = malloc(sizeof(MSTResult));
    result->edges = malloc((g->nv - 1) * sizeof(mst_edge_t));
    result->num_edges = 0;
    result->total_weight = 0;

    // 5. Iterate through sorted edges
    for (int i = 0; i < max_edges; i++) {
        int u = all_edges[i].u;
        int v = all_edges[i].v;
        int weight = all_edges[i].weight;

        // If adding this edge doesn't form a cycle
        if (dsu_find(dsu, u) != dsu_find(dsu, v)) {
            // Add it to the result
            result->edges[result->num_edges].u = u;
            result->edges[result->num_edges].v = v;
            result->edges[result->num_edges].weight = weight;
            result->total_weight += weight;
            result->num_edges++;

            // Union the two sets
            dsu_union(dsu, u, v);

            // Stop if we have V-1 edges
            if (result->num_edges == g->nv - 1) break;
        }
    }

    // Cleanup
    free(all_edges);
    dsu_destroy(dsu);

    return result;
}


// ============================================================
// Prim's Algorithm
// ============================================================

MSTResult* prim_mst(graph_t* g, int start_node) {
    if (g == NULL || start_node < 0 || start_node >= g->nv) return NULL;

    // Count all edges to safely size the Priority Queue
    // (A PQ without a decrease-key function might insert V items multiple times)
    int total_edge_references = 0;
    for (int i = 0; i < g->nv; i++) {
        for (edge_t* e = g->adjList[i]; e != NULL; e = e->next) {
            total_edge_references++;
        }
    }

    // key[i] stores the minimum weight edge to connect vertex i to the MST
    int* key = malloc(g->nv * sizeof(int));
    // mstSet[i] is true if vertex i is included in MST
    bool* mstSet = malloc(g->nv * sizeof(bool));
    // parent[i] stores the parent of i in the MST
    int* parent = malloc(g->nv * sizeof(int));

    for (int i = 0; i < g->nv; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
        parent[i] = -1;
    }

    // Initialize PQ with safe capacity
    pq_t* pq = pq_create(total_edge_references + 1);

    // Start with the first vertex
    key[start_node] = 0;
    item_t start_item = {-key[start_node], start_node}; // {-priority, value}
    pq_insert(pq, start_item);

    int total_weight = 0;

    while (!pq_is_empty(pq)) {
        // Extract vertex with the smallest key value
        item_t u_item = pq_extract_max(pq);
        int u = u_item.value;

        // If we've already included this node, skip.
        if (mstSet[u]) continue;

        mstSet[u] = true;

        // Add to the total weight only if we are connecting via a valid edge
        if (parent[u] != -1) {
            total_weight += key[u];
        }

        // Iterate through all adjacent vertices of u
        for (edge_t* e = g->adjList[u]; e != NULL; e = e->next) {
            int v = e->dest;
            int weight = e->weight;

            // If v is not in MST and weight of (u,v) is smaller than current key of v
            if (!mstSet[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                item_t v_item = {-key[v], v}; // Use negative key for min-heap behavior
                pq_insert(pq, v_item);
            }
        }
    }

    // Build the result struct
    MSTResult* result = malloc(sizeof(MSTResult));
    result->edges = malloc((g->nv - 1) * sizeof(mst_edge_t));
    result->num_edges = 0;
    result->total_weight = total_weight;

    for (int i = 0; i < g->nv; ++i) {
        if (parent[i] != -1) {
            result->edges[result->num_edges].u = parent[i];
            result->edges[result->num_edges].v = i;
            result->edges[result->num_edges].weight = key[i];
            result->num_edges++;
        }
    }

    // Cleanup
    free(key);
    free(mstSet);
    free(parent);
    pq_destroy(pq);

    return result;
}